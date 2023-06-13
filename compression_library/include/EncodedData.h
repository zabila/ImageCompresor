#pragma once

#include <vector>

const unsigned char WHITE = 0xFF;
const unsigned char BLACK = 0x00;
const int COMPRESS_THRESHOLD = 4;

struct EncodedData {
    int width;
    int height;
    std::vector<bool> emptyIndexes;
    std::vector<unsigned char> data;
};