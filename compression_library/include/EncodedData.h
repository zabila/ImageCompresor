#pragma once

#include <vector>

struct EncodedData {
    int width;
    int height;
    std::vector<bool> rowEmpty;
    std::vector<unsigned char> data;
};