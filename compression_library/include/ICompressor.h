#pragma once

#include "IEncoder.h"
#include "IDecoder.h"
#include "RawImageData.h"

#include <memory>
#include <string>


struct ICompressor {
    virtual std::shared_ptr<IEncoder> createEncoder() = 0;

    virtual std::shared_ptr<IDecoder> createDecoder() = 0;

    virtual void saveEncodedDataToFile(const std::string &filename, const EncodedData &data) const = 0;

    virtual EncodedData loadEncodedDataFromFile(const std::string &filename) const = 0;

    virtual void saveRawImageToFile(const std::string &filename, const RawImageData &data) const = 0;

    virtual RawImageData loadRawImageFromFile(const std::string &filename) const = 0;

    virtual ~ICompressor() = default;
};
