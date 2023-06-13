#pragma once

#include "IEncoder.h"
#include "EncodedData.h"
#include "RawImageData.h"

#include <vector>

class ImageEncoder : public IEncoder
{
public:
    EncodedData encode(const RawImageData& rawImageData) override;
};
