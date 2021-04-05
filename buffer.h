#pragma once
#include <string>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <istream>

struct BufferS{
    std::string zipCode;
    std::string placeName;
    std::string state;
    std::string county;
    std::string lat;
    std::string lon;
};

struct BufferData {
    unsigned int zipCode;
    std::string placeName;
    std::string state;
    std::string county;
    float lat;
    float lon;
};

// Different filetypes to read from
// Compile-time values faster than enum??
#define FILETYPE_CSV 0
#define FILETYPE_LEN_CSV 1
#define FILETYPE_INDEX_SORTED 2

#define FILEEXT_CSV "csv"
#define FILEEXT_LEN_CSV "lencsv"
#define FILEEXT_INDEX_SORTED "sindex"

class BufferRead {
    std::string dataFile;
    int fileType = -1;
    int curIndex;

    BufferS readNext_csv();
    BufferS readNext_lencsv();
    BufferS readNext_indexsorted();
    
public:
    BufferRead(std::string dataFile, int type);
    BufferRead(std::string dataFile);
    BufferS readNext();
    BufferData getFrom(BufferS);

    void print(BufferS);
    void print(BufferData);
};
