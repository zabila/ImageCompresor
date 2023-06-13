#pragma once

#include "RawImageData.h"
#include "EncodedData.h"

struct IDecoder
{
    virtual RawImageData decode(const EncodedData& data) = 0;

    virtual ~IDecoder() {}
};
