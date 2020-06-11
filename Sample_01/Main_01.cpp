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
    //read the contents of a file
    file_handler handler("lorem_ipsum");

    //display the contents
    cout << handler << endl << endl;

    //add some lines after the 4th line
    handler.add_after(handler[3], "------------- inserted line -----------------");

    //display the contents
    cout << handler << endl << endl;

    //reprint in a new file
    handler.reprint("lorem_ipsum_modified");

    //check the content of lorem_ipsum_modified

    return 0;
}
