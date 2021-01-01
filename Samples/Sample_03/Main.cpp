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
    //read the Salutations contents
    FileHandler Salutation("Salutations");

    //replace all bye with bye bye
    Salutation.replaceLine("bye", "bye bye");

    //replace the 3rd goodbye with lines: {"good morning","good afternoon","good eveninig"}
    Salutation.replaceLine("goodbye" , FileHandler::pack("good morning","good afternoon","good eveniiing"), 3);

    //print in a new file the modified contents
    Salutation.reprint("Salutations_modified_bugged");

    //replace  good eveniiing with good evening
    Salutation.replaceLine("good eveniiing" , "good evening");

    //print in a new file the modified contents
    Salutation.reprint("Salutations_modified");

    //check the content of Salutations_modified

    return 0;
}
