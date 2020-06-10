#include "../src/file_handler.h"
#include <iostream>
using namespace std;

int main(){
    //read the Salutations contents
    file_handler Salutation("Salutations");

    //replace all bye with bye bye
    Salutation.replace_line("bye", "bye bye");

    //reaplce the 3rd goodbye with lines: {"good morning","good afternoon","good eveninig"}
    Salutation.replace_line("goodbye" , file_handler::pack({"good morning","good afternoon","good eveninig"}), 3);

    //print in a new file the modified contents
    Salutation.reprint("Salutations_modified");

    //check the content of Salutations_modified

    return 0;
}
