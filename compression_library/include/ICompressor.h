#pragma once

#include "IEncoder.h"
#include "IDecoder.h"
#include "RawImageData.h"

#include <memory>
#include <string>

/**
 * @brief Interface for a compressor.
 *
 * This interface defines the methods for creating an encoder and a decoder.
 *
 */
struct ICompressor
{
    /**
     * @brief Creates an encoder.
     *
     * This method creates and returns a shared pointer to an encoder object.
     *
     * @return std::shared_ptr<IEncoder> A shared pointer to an encoder object.
     */
    virtual std::shared_ptr<IEncoder> createEncoder() = 0;

    /**
     * @brief Creates a decoder.
     *
     * This method creates and returns a shared pointer to a decoder object.
     *
     * @return std::shared_ptr<IDecoder> A shared pointer to a decoder object.
     */
    virtual std::shared_ptr<IDecoder> createDecoder() = 0;

    /**
     * Saves the encoded data to a file.
     *
     * This function saves the given encoded data to a file with the specified filename.
     *
     * @param filename The name of the file to save the encoded data to.
     * @param data The encoded data to be saved.
     *
     * @throws std::runtime_error If there is an error saving the data to the file.
     */
    virtual void saveEncodedDataToFile(const std::string& filename, const EncodedData& data) const = 0;

    /**
     * Loads encoded data from a file.
     *
     * This function loads encoded data from a file with the specified filename and returns it.
     *
     * @param filename The name of the file to load the encoded data from.
     *
     * @return The loaded encoded data.
     *
     * @throws std::runtime_error If there is an error loading the data from the file.
     */
    virtual EncodedData loadEncodedDataFromFile(const std::string& filename) const = 0;

    /**
     * Saves the raw image data to a file.
     *
     * This function takes in a filename and a `RawImageData` object and saves the raw image data to a file with the specified filename.
     *
     * @param filename The name of the file to save the raw image data to.
     * @param data The `RawImageData` object containing the raw image data to be saved.
     *
     * @throws std::runtime_error If there is an error saving the raw image data to the file.
     *
     * @note This function is virtual and must be implemented by derived classes.
     */
    virtual void saveRawImageToFile(const std::string& filename, const RawImageData& data) const = 0;

    /**
     * Loads the raw image data from a file.
     *
     * This function takes in a filename and loads the raw image data from the specified file.
     *
     * @param filename The name of the file to load the raw image data from.
     *
     * @return The `RawImageData` object containing the loaded raw image data.
     *
     * @throws std::runtime_error If there is an error loading the raw image data from the file.
     *
     * @note This function is virtual and must be implemented by derived classes.
     */
    virtual RawImageData loadRawImageFromFile(const std::string& filename) const = 0;

    virtual ~ICompressor() = default;
};
