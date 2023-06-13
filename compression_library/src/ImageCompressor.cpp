#include "ImageCompressor.h"

#include "ImageEncoder.h"
#include "ImageDecoder.h"

std::shared_ptr<IEncoder> ImageCompressor::createEncoder()
{
    return std::make_shared<ImageEncoder>();
}

std::shared_ptr<IDecoder> ImageCompressor::createDecoder()
{
    return std::make_shared<ImageDecoder>();
}
