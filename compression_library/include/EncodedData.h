#pragma once

#include <vector>

#include "RawImageData.h"

const unsigned char WHITE = 0xFF;
const unsigned char BLACK = 0x00;
const int COMPRESS_THRESHOLD = 4;

struct EncodedData
{
    EncodedData() = default;
    EncodedData(const RawImageData& raw_image_data);

    int width;
    int height;
    std::vector<char> emptyIndexes;
    std::vector<unsigned char> data;
};

inline EncodedData::EncodedData(const RawImageData& raw_image_data)
    : width(raw_image_data.width)
    , height(raw_image_data.height)
{
}
