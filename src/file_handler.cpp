/**
 * Author:    Andrea Casalino
 * Created:   01.06.2020
*
* report any bug to andrecasa91@gmail.com.
**/

#include "file_handler.h"
#include <fstream>
#include <iostream>
using namespace std;

file_handler::file_handler() { }

file_handler::file_handler(const std::string& file_location) : file_handler() {
    ifstream f(file_location);
    if(!f.is_open()) {
#ifdef ENABLE_COUT_WARNING
        cout << "unable to open file\n";
#endif
        f.close();
        throw 0; 
    }
    while (!f.eof()){
        this->__contents.emplace_back();
        getline(f, this->__contents.back());
    }
    f.close();
}

file_handler::file_handler(const file_handler& o) : __contents(o.__contents) {};

void file_handler::operator=(const file_handler& o){ this->__contents = o.__contents; }

const string& file_handler::operator[](const size_t& line_number) const{
    cout << "size : " << this->__contents.size() << endl;
    if(line_number >= this->__contents.size()) throw 0; //inexistent line
    auto it=this->__contents.begin();
    advance(it, line_number);
    return *it;
}

void file_handler::reprint(const std::string& file_location) const {
    ofstream f(file_location);
    if(!f.is_open()) {
#ifdef ENABLE_COUT_WARNING
        cout << "unable to create file\n";
#endif
        f.close();
        throw 0; 
    }
    f << *this;
    f.close();
}

ostream& operator<<(ostream& stream, const file_handler& contents){
    auto lines = contents.get_contents();
    auto it=lines.begin();
    stream << *it;
    ++it;
    for(it; it!=lines.end(); ++it) stream << endl << *it;
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



std::string file_handler::pack(const std::list<std::string>& to_pack){
    std::string packed;
    auto it=to_pack.begin();
    packed += *it;
    ++it;
    for( it; it!=to_pack.end(); ++it) {
        packed += "\n"; 
        packed += *it;
    }
    return move(packed);
};

void file_handler::push_back(const std::string& to_add){ 
    this->__contents.emplace_back(to_add); 
    auto end = this->__contents.end();
    --end;
    check_for_split(this->__contents, end);
}

void file_handler::push_front(const std::string& to_add){ 
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



void file_handler::replace_line(const std::string& to_remove, const std::string& to_put, const size_t& istances){
    auto pos = find(this->__contents , to_remove, istances);
    for(auto it = pos.begin(); it!=pos.end(); ++it)  {
        **it = to_put;
        check_for_split(this->__contents, *it);
    }
}

void file_handler::remove_line(const std::string& to_remove, const size_t& istances){
    auto pos = find(this->__contents , to_remove, istances);
    for(auto it = pos.begin(); it!=pos.end(); ++it) this->__contents.erase(*it);
}

void file_handler::add_before(const std::string& involved_line, const std::string& to_put, const size_t& istances){
    auto pos = find(this->__contents , involved_line, istances);
    for(auto it = pos.begin(); it!=pos.end(); ++it) {
        this->__contents.insert(*it, to_put);
        auto it_prev =*it;
        --it_prev;
        check_for_split(this->__contents, it_prev);
    }
}

void file_handler::add_after(const std::string& involved_line, const std::string& to_put, const size_t& istances){
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

