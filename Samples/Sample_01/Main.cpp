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
    //read the contents of a file
    FileHandler handler("lorem_ipsum");

    //display the contents
    cout << handler << endl << endl;

    //add some lines after the 4th line
    handler.addAfter(handler[3], "------------- inserted line -----------------");

    //display the contents
    cout << handler << endl << endl;

    //reprint in a new file
    handler.reprint("lorem_ipsum_modified");

    //check the content of lorem_ipsum_modified

    return 0;
}
