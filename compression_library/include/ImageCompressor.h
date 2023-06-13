#pragma once

#include "ICompressor.h"

#include <memory>

class ImageCompressor : public ICompressor {
public:
    std::shared_ptr<IEncoder> createEncoder() override;

    std::shared_ptr<IDecoder> createDecoder() override;

    void saveToFile(const std::string &filename, const EncodedData &data) const override;

    EncodedData loadFromFile(const std::string &filename) const override;

};