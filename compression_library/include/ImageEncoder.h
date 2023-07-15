#pragma once

#include "IEncoder.h"
#include "EncodedData.h"
#include "RawImageData.h"

#include <vector>

/**
 * @brief ImageEncoder class that implements the IEncoder interface.
 *
 * This class is responsible for encoding raw image data into an encoded format.
 * It inherits from the IEncoder interface and provides an implementation for the encode() method.
 */
class ImageEncoder : public IEncoder
{
public:
    /**
     * @brief Encodes the given raw image data into an encoded format.
     *
     * This method takes a reference to a RawImageData object and encodes it into an EncodedData object.
     * The encoding process converts the raw image data into a compressed or encoded format, such as JPEG or PNG.
     *
     * @param rawImageData The raw image data to be encoded.
     * @return The encoded data in the form of an EncodedData object.
     */
    EncodedData encode(const RawImageData& rawImageData) override;
};
