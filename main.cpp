#include <iostream>
#include "buffer.h"



int main(int argc, char *argv[]){
    if (argc <= 1){
        // this error should be better
        std::cerr << "Requires at least one argument!" << std::endl;
        return -1;
    }

    std::string filename(argv[1]); // get as string

    BufferRead br(filename); // let's see how this goes
    BufferS buff = br.readNext();
    br.print(buff);

}