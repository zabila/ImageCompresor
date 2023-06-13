#pragma once

#include "IDecoder.h"
#include "EncodedData.h"
#include "RawImageData.h"

class ImageDecoder : public IDecoder
{
public:
    RawImageData decode(const EncodedData& data) override;
};
