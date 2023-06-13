#pragma once

#include "RawImageData.h"
#include "EncodedData.h"

struct IEncoder
{
    virtual EncodedData encode(const RawImageData& data) = 0;

    virtual ~IEncoder() = default;
};
