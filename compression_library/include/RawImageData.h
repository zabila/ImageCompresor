#pragma once

#include <vector>

struct RawImageData {
    int width;
    int height;
    std::vector<unsigned char> data;
};