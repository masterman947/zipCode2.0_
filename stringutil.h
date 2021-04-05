#pragma once

#include <string>
#include <vector>
#include <bits/stdc++.h>

namespace util{

    std::vector<std::string> getTokens(std::string str, char delim);

    std::vector<std::string> getTokensLen(std::string str, bool lenMarkerIncludesSelf);
}