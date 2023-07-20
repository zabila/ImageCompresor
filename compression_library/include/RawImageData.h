#pragma once

#include <vector>

struct RawImageData
{
    int width;
    int height;
    std::vector<unsigned char> data;

    bool is_valid() const { return width > 0 && height > 0 && !data.empty(); }
};
