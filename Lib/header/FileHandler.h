/**
 * Author:    Andrea Casalino
 * Created:   01.06.2020
*
* report any bug to andrecasa91@gmail.com.
**/

#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <string>
#include <list>
#include <ostream>
#include <sstream>

namespace fh {
    /* This class can be used to import or print textual files.
    It internally stores the contents of a file (to read or to print) as a list of strings (one for each line). 
    */
    class FileHandler {
    public:
        /* Default constructor: it initializes the contents as an empty string.  
        */
        FileHandler() = default;

        /* Builds the contents by reading the file at the passed location (relative and absolute path are accepted) .
        In case the file is not importable, the object is built like done in the default constructor.
        */
        explicit FileHandler(const std::string& file_location);

        /* Copy constructor: the contents are copied from the passed FileHandler.
        */
        FileHandler(const FileHandler& o) = default;

        /* Assignment operator: the contents are deleted and copied from the passed FileHandler.
        */
        FileHandler& operator=(const FileHandler& o) = default;

        /* Move constructor: the contents are moved from the passed FileHandler.
        * The passed object is left empty
        */
        FileHandler(FileHandler&& o) = default;

        /* Assignment move operator: the contents are moved from the passed FileHandler.
        * The passed object is left empty
        */
        FileHandler& operator=(FileHandler&& o) = default;

        /* Returns a specific line in the content.
        * throw if the line number is out of bounds.
        */
        const std::string& operator[](const size_t& line_number) const;

        /* Creates a file in the passed location, writing the contents currently stored in this object.  
        */
        void reprint(const std::string& file_location) const;

        /* Get the contents stored in this object.
        */
        inline const std::list<std::string>& getContents() const { return this->__contents; };

        /* Takes a list of lines and compacts them into a single one, using the separator character '\n'.
        For example when passsing {"lineA", "lineB", "lineC"} the returned result is "lineA\nlineB\nlineC".
        You can use this function to pass multiple lines as an input to: 
        FileHandler::replaceLine, FileHandler::addBefore, FileHandler::addAfter, FileHandler::removeLine, FileHandler::pushBack, FileHandler::pushFront  
        */
        static std::string pack(const std::list<std::string>& to_pack);

        /* Similar to pack(const std::list<std::string>& to_pack), but using variadic arguments
        At least one string should be passed to the function.
        */
        template<typename ... Args>
        static std::string pack(Args ... args) {
            std::stringstream stream;
            pack(stream, args...);
            return stream.str();
        };

        /* Remove from the contents the specified line(s).
        In case istances is passed = 0, all the lines in the contents matching with to_remove are remove.
        On the opposite, when passing a number n>0, the n^th istances of to_remove that is present in the contents
        is affected by this method (if exists, otherwise nothing is done). 
        */
        void removeLine(const std::string& to_remove, const size_t& istances = 0);
        
        /* Replaces to_remove with to_put.
        Istances has a similar meaning as the istances passed to FileHandler::removeLine, considering to_remove
        */
        void replaceLine(const std::string& to_replace, const std::string& to_put, const size_t& istances = 0);

        /* Adds to_put before involved_line in the contents.
        Istances has a similar meaning as the istances passed to FileHandler::removeLine, considering involved_line
        */
        void addBefore(const std::string& involved_line, const std::string& to_put, const size_t& istances = 0);

        /* Adds to_put after involved_line in the contents.
        Istances has a similar meaning as the istances passed to FileHandler::removeLine, considering involved_line
        */
        void addAfter(const std::string& involved_line, const std::string& to_put, const size_t& istances = 0);

        /* Adds at the end of the contents to_add.
        */
        void pushBack(const std::string& to_add);

        /* Adds at the beginning of the contents to_add.
        */
        void pushFront(const std::string& to_add);

        friend std::ostream& operator<<(std::ostream&, const FileHandler&);
        friend std::stringstream& operator<<(std::stringstream&, const FileHandler&);

    private:
        template<typename ... Args>
        static void pack(std::stringstream& stream, const std::string& val, Args ... remaining) {
            stream << val << '\n';
            pack(stream, remaining...);
        };

        template<typename ... Args>
        static void pack(std::stringstream& stream, const char* val, Args ... remaining) {
            stream << val << '\n';
            pack(stream, remaining...);
        };

        static void pack(std::stringstream& stream, const std::string& val);

        static void pack(std::stringstream& stream, const char* val);

        template<typename Stream>
        void passToStream(Stream& stream) const {
            if(!this->__contents.empty()) {
                auto it=this->__contents.begin();
                stream << *it;
                ++it;
                for(it; it!=this->__contents.end(); ++it) stream << std::endl << *it;
            }
        };

    // data
        std::list<std::string>  __contents;
    };


    /* Similar to file_handler::reprint, but passing the content to the passed stream wihtout creating a textual file.
    */
    std::ostream& operator<<(std::ostream& stream, const FileHandler& contents);

    std::stringstream& operator<<(std::stringstream& stream, const FileHandler& contents);
}

#endif