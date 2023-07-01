#pragma once

#include "RawImageData.h"
#include "EncodedData.h"

/**
 * @interface IDecoder
 * @brief Interface for decoding encoded data into raw image data.
 */
struct IDecoder
{
    /**
     * @brief Decodes the given encoded data into raw image data.
     * @param data The encoded data to be decoded.
     * @return The decoded raw image data.
     * @throws std::runtime_error if the decoding process fails.
     */
    virtual RawImageData decode(const EncodedData& data) = 0;

    virtual ~IDecoder() = default;
};
