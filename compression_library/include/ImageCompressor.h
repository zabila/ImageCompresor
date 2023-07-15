#pragma once

#include "ICompressor.h"

class ImageCompressor : public ICompressor
{
public:
    std::shared_ptr<IEncoder> createEncoder() override;
    std::shared_ptr<IDecoder> createDecoder() override;

    void saveEncodedDataToFile(const std::string& filename, const EncodedData& data) const override;
    EncodedData loadEncodedDataFromFile(const std::string& filename) const override;
    void saveRawImageToFile(const std::string& filename, const RawImageData& imageData) const override;
    RawImageData loadRawImageFromFile(const std::string& filename) const override;
};
