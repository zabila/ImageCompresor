#pragma once

#include "IEncoder.h"
#include "IDecoder.h"

#include <memory>

struct ICompressor
{
    virtual std::shared_ptr<IEncoder> createEncoder() = 0;
    virtual std::shared_ptr<IDecoder> createDecoder() = 0;

    virtual ~ICompressor() {}
};
