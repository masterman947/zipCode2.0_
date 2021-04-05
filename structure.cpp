#include "structure.h"

using namespace std;

string structure::CSV::bts(BufferData data){
    string line = "";
    line += to_string(data.zipCode) + ",";
    line += data.placeName + ",";
    line += data.state + ",";
    line += data.county + ",";
    line += to_string(data.lat) + ",";
    line += to_string(data.lon) + ",";
    return line;
}


string structure::CSV::bts(BufferS sdata){
    string line = "";
    line += sdata.zipCode + ",";
    line += sdata.placeName + ",";
    line += sdata.state + ",";
    line += sdata.county + ",";
    line += sdata.lat + ",";
    line += sdata.lon + ",";
    return line;
}

void structure::CSV::write(BufferData data){
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

void structure::CSV::writeAll(vector<BufferData> data){
    for(vector<BufferData>::iterator i = data.begin(); i != data.end(); i++){
        BufferData data = *i;
        write(data);
    }
}
