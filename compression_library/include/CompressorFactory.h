#pragma once

#include "ICompressor.h"

#include <memory>

class CompressorFactory
{
public:
    static std::shared_ptr<ICompressor> createCompressor();
};