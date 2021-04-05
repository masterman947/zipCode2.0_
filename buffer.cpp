#include "buffer.h"


BufferRead::BufferRead(std::string dataFile, int type){
    this->dataFile = dataFile;
    this->fileType = type;
}

BufferRead::BufferRead(std::string dataFile){
    // guess at filetype
    this->dataFile = dataFile;

    std::size_t extIndex = dataFile.find_last_of(".");
    std::string ext = dataFile.substr(extIndex+1);
    if (ext.compare(FILEEXT_CSV) == 0){
        // we are using a csv file
        fileType = FILETYPE_CSV;
    }
    if (ext.compare(FILEEXT_LEN_CSV) == 0){
        // we are using a csv file
        fileType = FILETYPE_LEN_CSV;
    }
    if (ext.compare(FILEEXT_INDEX_SORTED) == 0){
        // we are using a csv file
        fileType = FILETYPE_INDEX_SORTED;
    }
    assert(fileType != -1); // Not sure what assertion does?

    /* For now let's be aggressive
    if (fileType == -1){
        // failed to determine filettype
        std::cerr << "Failed to determine filetype for \"" << dataFile.c_str() << "\"" << std::endl;
    }*/
}

BufferS BufferRead::readNext_csv(){
    return BufferS();
}
BufferS BufferRead::readNext_lencsv(){
    return BufferS();
}
BufferS BufferRead::readNext_indexsorted(){
    return BufferS();
}


BufferS BufferRead::readNext(){
    // just pass logic on to appropriate function.
    // No need to think about this externally
    switch(fileType){
        case FILETYPE_CSV:
            return readNext_csv();
        case FILETYPE_INDEX_SORTED:
            return readNext_indexsorted();
        case FILETYPE_LEN_CSV:
            return readNext_lencsv();
    }
    std::cerr << "BufferRead has an invalid file type. Must be CSV, LEN_CSV, or INDEX_SORTED\n\tfile="<<dataFile.c_str()<<">>>>\n\ttype=" << fileType << std::endl;
    return BufferS(); // shouldn't happen
}

BufferData BufferRead::getFrom(BufferS src){
    // parse strings to values
    return BufferData();
}

void BufferRead::print(BufferS buff){
    std::cout << "BufferData:" << std::endl;
    std::cout << "\tZipCode=" << buff.zipCode.c_str() << std::endl;
    std::cout << "\tPlaceName=" << buff.placeName.c_str() << std::endl;
    std::cout << "\tState=" << buff.state.c_str() << std::endl;
    std::cout << "\tCounty=" << buff.county.c_str() << std::endl;
    std::cout << "\tZipCode=" << buff.lat.c_str() << std::endl;
    std::cout << "\tZipCode=" << buff.lon.c_str() << std::endl;

}


void BufferRead::print(BufferData buff){
    std::cout << "BufferData:" << std::endl;
    std::cout << "\tZipCode=" << buff.zipCode << std::endl;
    std::cout << "\tPlaceName=" << buff.placeName.c_str() << std::endl;
    std::cout << "\tState=" << buff.state.c_str() << std::endl;
    std::cout << "\tCounty=" << buff.county.c_str() << std::endl;
    std::cout << "\tZipCode=" << buff.lat << std::endl;
    std::cout << "\tZipCode=" << buff.lon << std::endl;
}
