#include "stringutil.h"

std::vector<std::string> util::getTokens(std::string str, char delim){
    std::vector<std::string> tokens;
    std::stringstream stream(str);
    std::string token;
    while(std::getline(stream, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> util::getTokensLen(std::string str, bool lenMarkerIncludesSelf){
    std::vector<std::string> tokens;
    //TODO add in functionality
    return tokens;
}