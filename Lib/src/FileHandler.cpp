/**
 * Author:    Andrea Casalino
 * Created:   01.06.2020
*
* report any bug to andrecasa91@gmail.com.
**/

#include <FileHandler.h>
#include <fstream>
using namespace std;

namespace fh {
    FileHandler::FileHandler(const std::string& file_location) : FileHandler() {
        ifstream f(file_location);
        if(!f.is_open()) {
            f.close();
            return; 
        }
        while (!f.eof()){
            this->__contents.emplace_back();
            getline(f, this->__contents.back());
        }
        f.close();
    }

    const string& FileHandler::operator[](const size_t& line_number) const{
        if(line_number >= this->__contents.size()) throw std::runtime_error("line_number out of bounds");
        auto it=this->__contents.begin();
        advance(it, line_number);
        return *it;
    }

    void FileHandler::reprint(const std::string& file_location) const {
        ofstream f(file_location);
        if(!f.is_open()) {
            f.close();
            return; 
        }
        f << *this;
        f.close();
    }

    ostream& operator<<(ostream& stream, const FileHandler& contents){
        contents.passToStream<ostream>(stream);
        return stream;
    }

    std::stringstream& operator<<(std::stringstream& stream, const FileHandler& contents) {
        contents.passToStream<stringstream>(stream);
        return stream;
    }

    void check_for_split(list<string>& source, list<string>::iterator& line){
        list<size_t> split_pos;
        size_t k,K=(*line).size();
        for(k=0;k<K; ++k){
            if((*line)[k] == '\n') split_pos.push_back(k);
        }
        if(split_pos.empty()) return;

        auto next = line;
        ++next;

        split_pos.push_back(K);
        K = split_pos.size() - 1;
        auto it_pos = split_pos.begin();
        auto it_pos_next = it_pos;
        ++it_pos_next;
        for(k=0; k<K; ++k){
            string temp(*line , *it_pos + 1, *it_pos_next - *it_pos -1);
            source.insert(next, temp);
            ++it_pos;
            ++it_pos_next;
        }

        *line = string(*line, 0, split_pos.front());
    }

    std::string FileHandler::pack(const std::list<std::string>& to_pack){
        std::stringstream temp;
        if(!to_pack.empty()) {
            auto it = to_pack.begin();
            temp << '\n' << *it;
            ++it;
            for(it; it!=to_pack.end(); ++it) {
                temp << *it;
            }
        }
        return temp.str();
    };

    void FileHandler::pack(std::stringstream& stream, const std::string& val) {
        stream << val;
    }

    void FileHandler::pack(std::stringstream& stream, const char* val) {
        stream << val;
    }

    void FileHandler::pushBack(const std::string& to_add){ 
        this->__contents.emplace_back(to_add); 
        auto end = this->__contents.end();
        --end;
        check_for_split(this->__contents, end);
    }

    void FileHandler::pushFront(const std::string& to_add){ 
        this->__contents.emplace_front(to_add); 
        auto start = this->__contents.begin();
        check_for_split(this->__contents, start);
    }

    list<list<string>::iterator> find(std::list<std::string>& contents, const string& to_find, const size_t& istances){
        list<list<string>::iterator> positions;
        if(istances == 0){
            for(auto it=contents.begin(); it!=contents.end(); ++it) {
                if(it->compare(to_find) == 0) positions.emplace_back(it);
            }
        }
        else{
            size_t c = 1;
            for(auto it=contents.begin(); it!=contents.end(); ++it) {
                if(it->compare(to_find) == 0){
                    if(c == istances){
                        positions.emplace_back(it);
                        break;
                    }
                    else ++c;
                }
            }
        }
        return positions;
    };

    void FileHandler::replaceLine(const std::string& to_remove, const std::string& to_put, const size_t& istances){
        auto pos = find(this->__contents , to_remove, istances);
        for(auto it = pos.begin(); it!=pos.end(); ++it)  {
            **it = to_put;
            check_for_split(this->__contents, *it);
        }
    }

    void FileHandler::removeLine(const std::string& to_remove, const size_t& istances){
        auto pos = find(this->__contents , to_remove, istances);
        for(auto it = pos.begin(); it!=pos.end(); ++it) this->__contents.erase(*it);
    }

    void FileHandler::addBefore(const std::string& involved_line, const std::string& to_put, const size_t& istances){
        auto pos = find(this->__contents , involved_line, istances);
        for(auto it = pos.begin(); it!=pos.end(); ++it) {
            this->__contents.insert(*it, to_put);
            auto it_prev =*it;
            --it_prev;
            check_for_split(this->__contents, it_prev);
        }
    }

    void FileHandler::addAfter(const std::string& involved_line, const std::string& to_put, const size_t& istances){
        auto pos = find(this->__contents , involved_line, istances);
        for(auto it = pos.begin(); it!=pos.end(); ++it) {
            auto it_temp = *it;
            ++it_temp;
            this->__contents.insert(it_temp, to_put);
            auto it_prev = it_temp;
            --it_prev;
            check_for_split(this->__contents, it_prev);
        }
    }

}
