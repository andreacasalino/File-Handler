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

namespace fh {

    /* This class can be used to import or print textual files.
    It internally stores the contents of a file (to read or to print) as a list of strings (one for each line). 
    */
    class file_handler {
    public:
        /* Default constructor: it initializes the contents as an empty string.  
        */
        file_handler();

        /* Builds the contents by reading the file at the passed location (relative and absolute path are accepted) .
        */
        file_handler(const std::string& file_location);

        /* Copy constructor: the contents are copied from the passed file_handler.
        */
        file_handler(const file_handler& o);

        /* Assignment operator: the contents are deleted and copied from the passed file_handler.
        */
        void operator=(const file_handler& o);

        /* Returns a specific line in the content.
        */
        const std::string& operator[](const size_t& line_number) const;

        /* Creates a file in the passed location, writing the contents currently stored in this object.  
        */
        void reprint(const std::string& file_location) const;

        /* Get the contents stored in this object.
        */
        const std::list<std::string>& get_contents() const { return this->__contents; };

        /* Takes a list of lines and compacts them into a single one, using the separator character '\n'.
        For example when passsing {"lineA", "lineB", "lineC"} the returned result is "lineA\nlineB\nlineC".
        You can use this function to pass multiple lines as an input to: 
        file_handler::replace_line, file_handler::add_before, file_handler::add_after, file_handler::remove_line, file_handler::push_back, file_handler::push_front  
        */
        static std::string pack(const std::list<std::string>& to_pack);

        /* Remove from the contents the specified line(s).
        In case istances is passed = 0, all the lines in the contents matching with to_remove are remove.
        On the opposite, when passing a number n>0, the n^th istances of to_remove that is present in the contents
        is affected by this method (if exists, otherwise nothing is done). 
        */
        void remove_line(const std::string& to_remove, const size_t& istances = 0);
        
        /* Replaces to_remove with to_put.
        Istances has a similar meaning as the istances passed to file_handler::remove_line, considering to_remove
        */
        void replace_line(const std::string& to_replace, const std::string& to_put, const size_t& istances = 0);

        /* Adds to_put before involved_line in the contents.
        Istances has a similar meaning as the istances passed to file_handler::remove_line, considering involved_line
        */
        void add_before(const std::string& involved_line, const std::string& to_put, const size_t& istances = 0);

        /* Adds to_put after involved_line in the contents.
        Istances has a similar meaning as the istances passed to file_handler::remove_line, considering involved_line
        */
        void  add_after(const std::string& involved_line, const std::string& to_put, const size_t& istances = 0);

        /* Adds at the end of the contents to_add.
        */
        void push_back(const std::string& to_add);

        /* Adds at the beginning of the contents to_add.
        */
        void push_front(const std::string& to_add);
    private:
    // data
        std::list<std::string>  __contents;
    };


    /* Similar to file_handler::reprint, but passing the content to the passed stream wihtout creating a textual file.
    */
    std::ostream& operator<<(std::ostream& stream, const file_handler& contents);

}

#endif