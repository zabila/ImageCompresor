#include "CompressorFactory.h"

#include "ImageCompressor.h"

std::shared_ptr<ICompressor> CompressorFactory::createCompressor()
{
    return std::make_shared<ImageCompressor>();
}
