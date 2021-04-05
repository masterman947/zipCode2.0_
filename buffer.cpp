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
    if (ext.compare(FILEEXT_INDEX_SORTED_DATA) == 0 || ext.compare(FILEEXT_INDEX_SORTED_INDEX) == 0){
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
    BufferS sbuff;
    if(!stream.is_open()){
        stream.open(dataFile.c_str(), std::ifstream::in);
        if (!hasReadHeader) hasReadHeader = true; // assume first line to be header
    }
    std::string line;
    std::getline(stream, line);
    std::vector<std::string> tokens = util::getTokens(line, ',');
    if(tokens.size() != 6) return sbuff; // return empty buffer if no data
    sbuff.zipCode = tokens[0];
    sbuff.placeName = tokens[1];
    sbuff.state = tokens[2];
    sbuff.county = tokens[3];
    sbuff.lat = tokens[4];
    sbuff.lon = tokens[5];
    return sbuff;
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
    return BufferData(src);
}

std::vector<BufferData> BufferRead::loadRecords(int count){
    std::vector<BufferData> records;
    assert(hasBufferReadHeader()); // if we haven't read the header externally, we messed up.

    for(int i = 0; i < count; i++){
        BufferS sbuff = readNext(); // get next record as string
        if(sbuff.zipCode.length() <= 1) break; // break if reached end
        BufferData data(sbuff); // parse as types
        records.push_back(BufferData(data)); // push to vector
    }

    return records;
}


void BufferRead::print(BufferS buff){
    std::cout << "BufferData:" << std::endl;
    std::cout << "\tZipCode=\"" << buff.zipCode.c_str() << "\"" << std::endl;
    std::cout << "\tPlaceName=\"" << buff.placeName.c_str() << "\"" << std::endl;
    std::cout << "\tState=\"" << buff.state.c_str() << "\"" << std::endl;
    std::cout << "\tCounty=\"" << buff.county.c_str() << "\"" << std::endl;
    std::cout << "\tZipCode=\"" << buff.lat.c_str() << "\"" << std::endl;
    std::cout << "\tZipCode=\"" << buff.lon.c_str() << "\"" << std::endl;

}


void BufferRead::print(BufferData buff){
    std::cout << "BufferData:" << std::endl;
    std::cout << "\tZipCode=" << buff.zipCode << std::endl;
    std::cout << "\tPlaceName=" << buff.placeName.c_str() << std::endl;
    std::cout << "\tState=" << buff.state.c_str() << std::endl;
    std::cout << "\tCounty=" << buff.county.c_str() << std::endl;
    std::cout << "\tLatitude=" << buff.lat << std::endl;
    std::cout << "\tLongitude=" << buff.lon << std::endl;
}


BufferData::BufferData(BufferS sbuff){
    zipCode = std::stoi(sbuff.zipCode);
    placeName = sbuff.placeName;
    state = sbuff.state;
    county = sbuff.county;
    lat = std::stof(sbuff.lat);
    lon = std::stof(sbuff.lon);
}
BufferS BufferData::toStringBuffer(){
    BufferS sbuff;
    sbuff.zipCode = std::to_string(zipCode);
    sbuff.placeName = placeName;
    sbuff.state = state;
    sbuff.county = county;
    sbuff.lat = std::to_string(lat);
    sbuff.lon = std::to_string(lon);
    return sbuff;
}

