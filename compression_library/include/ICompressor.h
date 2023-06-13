#pragma once

#include "IEncoder.h"
#include "IDecoder.h"

#include <memory>
#include <string>


struct ICompressor {
    virtual std::shared_ptr<IEncoder> createEncoder() = 0;

    virtual std::shared_ptr<IDecoder> createDecoder() = 0;

    virtual void saveToFile(const std::string &filename, const EncodedData &data) const = 0;

    virtual EncodedData loadFromFile(const std::string &filename) const = 0;

    virtual ~ICompressor() = default;
};
