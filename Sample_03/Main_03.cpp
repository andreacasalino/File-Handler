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
    //read the Salutations contents
    file_handler Salutation("Salutations");

    //replace all bye with bye bye
    Salutation.replace_line("bye", "bye bye");

    //replace the 3rd goodbye with lines: {"good morning","good afternoon","good eveninig"}
    Salutation.replace_line("goodbye" , file_handler::pack({"good morning","good afternoon","good eveniiing"}), 3);

    //print in a new file the modified contents
    Salutation.reprint("Salutations_modified_bugged");

    //replace  good eveniiing with good evening
    Salutation.replace_line("good eveniiing" , "good evening");

    //print in a new file the modified contents
    Salutation.reprint("Salutations_modified");

    //check the content of Salutations_modified

    return 0;
}
