#include <iostream>
#include "buffer.h"
#include "structure.h"
#include <chrono>


#define NUMBER_RECORDS 1000


int main(int argc, char *argv[]){
    if (argc <= 1){
        // this error should be better
        std::cerr << "Requires at least one argument!" << std::endl;
        return -1;
    }

    std::string filename(argv[1]); // get as string

    BufferRead br(filename); // select file
    BufferS header = br.readNext(); // get first record (should be header)

    structure::SortedIndex out("output");

    auto start = std::chrono::high_resolution_clock::now(); // get timing for process
    //

    out.writeHeader(header); // write header record

    std::vector<BufferData> records;
    do {
        records = br.loadRecords(NUMBER_RECORDS);
        out.writeAll(records);
    }while(records.size() > 0);// should read entire file in $NUMBER_RECORDS chunks

    //
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> fp_ms = stop - start;
    std::cout << "Completed process in " << fp_ms.count() << " milliseconds" << std::endl;

}