#include "structure.h"

using namespace std;


void structure::DataSystem::write(BufferData data){
    if (!os.is_open()){
        os.open(filepath, ios_base::out);
        if (!os.good()){
            mkdir(DATA_DIR, 0777);
            os.open(filepath, ios_base::out);
        }
        assert(os.good()); // at this point, we should be good
    }
    os << bts(data) << endl;
}

void structure::DataSystem::writeAll(vector<BufferData> data){
    if (!os.is_open()){ // copied because one check per record could be slower
        os.open(filepath, ios_base::out);
        if (!os.good()){
            mkdir(DATA_DIR, 0777);
            os.open(filepath, ios_base::out);
        }
        assert(os.good()); // at this point, we should be good
    }
    for(vector<BufferData>::iterator i = data.begin(); i != data.end(); i++){
        BufferData data = *i;
        os << bts(data) << endl;
    }
}

std::string structure::DataSystem::bts(BufferData data){
    return bts(data.toStringBuffer());
}

string structure::CSV::bts(BufferS sdata){
    string line = "";
    line += sdata.zipCode + ",";
    line += sdata.placeName + ",";
    line += sdata.state + ",";
    line += sdata.county + ",";
    line += sdata.lat + ",";
    line += sdata.lon;
    return line;
}

string structure::LenCSV::bts(BufferS data){
    string line = "";
    string tmp;
    string sizeMarker;

    tmp = data.zipCode;
    sizeMarker = to_string(tmp.size());
    if(sizeMarker.size() == 1) sizeMarker = "0"+sizeMarker;
    assert(sizeMarker.size() == 2);
    line += sizeMarker + tmp + ",";

    tmp = data.placeName;
    sizeMarker = to_string(tmp.size());
    if(sizeMarker.size() == 1) sizeMarker = "0"+sizeMarker;
    assert(sizeMarker.size() == 2);
    line += sizeMarker + tmp + ",";

    tmp = data.state;
    sizeMarker = to_string(tmp.size());
    if(sizeMarker.size() == 1) sizeMarker = "0"+sizeMarker;
    assert(sizeMarker.size() == 2);
    line += sizeMarker + tmp + ",";

    tmp = data.county;
    sizeMarker = to_string(tmp.size());
    if(sizeMarker.size() == 1) sizeMarker = "0"+sizeMarker;
    assert(sizeMarker.size() == 2);
    line += sizeMarker + tmp + ",";

    tmp = data.lat;
    sizeMarker = to_string(tmp.size());
    if(sizeMarker.size() == 1) sizeMarker = "0"+sizeMarker;
    assert(sizeMarker.size() == 2);
    line += sizeMarker + tmp + ",";

    tmp = data.lon;
    sizeMarker = to_string(tmp.size());
    if(sizeMarker.size() == 1) sizeMarker = "0"+sizeMarker;
    assert(sizeMarker.size() == 2);
    line += sizeMarker + tmp;

    return line;
}