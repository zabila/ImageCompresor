#pragma once

#include "IEncoder.h"
#include "EncodedData.h"
#include "RawImageData.h"

class ImageEncoder : public IEncoder
{
public:
    EncodedData encode(const RawImageData& data) override;
};
