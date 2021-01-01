/**
 * Author:    Andrea Casalino
 * Created:   01.06.2020
*
* report any bug to andrecasa91@gmail.com.
**/

#include <FileHandler.h>
#include <iostream>
using namespace std;
using namespace fh;

int main(){
    //init empty contents
    FileHandler handler;

    //add some lines
    handler.pushBack("This file");
    handler.pushBack("was generated from");
    handler.pushBack("a C++ application");
    handler.pushBack("This library is cool");
    handler.pushBack(FileHandler::pack("variadic args", "are easily", "handled"));

    //display the contents
    cout << handler << endl << endl;

    //add a smiling face before the last line
    handler.addBefore( handler.getContents().back(), "     :)     ");

    //print in a file
    handler.reprint("generated_file");

    //check the content of generated_file

    //pass the entire file content to a string stream
    std::stringstream stream;
    stream << handler;
    cout << stream.str() << endl;

    return 0;
}
