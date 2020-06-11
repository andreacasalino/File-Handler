/**
 * Author:    Andrea Casalino
 * Created:   01.06.2020
*
* report any bug to andrecasa91@gmail.com.
**/

#include "../src/file_handler.h"
#include <iostream>
using namespace std;

int main(){
    //init empty contents
    file_handler handler;

    //add some lines
    handler.push_back("This file");
    handler.push_back("was generated from");
    handler.push_back("a C++ application");
    handler.push_back("This library is cool");

    //display the contents
    cout << handler << endl << endl;

    //add a smiling face before the last line
    handler.add_before( handler.get_contents().back(), "     :)     ");

    //print in a file
    handler.reprint("generated_file");

    //check the content of generated_file

    return 0;
}
