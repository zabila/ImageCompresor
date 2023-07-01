#pragma once

#include "RawImageData.h"
#include "EncodedData.h"

/**
 * @brief Interface for encoding raw image data.
 *
 * This interface defines the contract for encoding raw image data into an encoded format.
 * Implementations of this interface should provide an implementation for the encode() method.
 */
struct IEncoder
{
    /**
     * @brief Encodes the given raw image data.
     *
     * This method takes in a reference to a RawImageData object and encodes it into an EncodedData object.
     *
     * @param data The raw image data to be encoded.
     * @return The encoded data.
     */
    virtual EncodedData encode(const RawImageData& data) = 0;

    virtual ~IEncoder() = default;
};
