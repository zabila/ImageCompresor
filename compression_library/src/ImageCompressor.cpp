#include "ImageCompressor.h"

#include "ImageEncoder.h"
#include "ImageDecoder.h"

#include <fstream>

std::shared_ptr<IEncoder> ImageCompressor::createEncoder() {
    return std::make_shared<ImageEncoder>();
}

std::shared_ptr<IDecoder> ImageCompressor::createDecoder() {
    return std::make_shared<ImageDecoder>();
}

void ImageCompressor::saveToFile(const std::string &filename, const EncodedData &data) const {
    if (filename.substr(filename.find_last_of(".") + 1) != "barch") {
        throw std::runtime_error("Invalid file extension. Only .barch files are supported.");
    }

    std::ofstream output(filename, std::ios::binary);
    if (!output) {
        throw std::runtime_error("Failed to open file for writing");
    }

    output.write(reinterpret_cast<const char *>(&data.width), sizeof(data.width));
    output.write(reinterpret_cast<const char *>(&data.height), sizeof(data.height));

    std::size_t size = data.emptyIndexes.size();
    output.write(reinterpret_cast<const char *>(&size), sizeof(size));

    for (const auto &index: data.emptyIndexes) {
        output.write(reinterpret_cast<const char *>(&index), sizeof(index));
    }

    for (const auto &byte: data.data) {
        output.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
    }
}

EncodedData ImageCompressor::loadFromFile(const std::string &filename) const {
    if (filename.substr(filename.find_last_of(".") + 1) != "barch") {
        throw std::runtime_error("Invalid file extension. Only .barch files are supported.");
    }

    std::ifstream input(filename, std::ios::binary);
    if (!input) {
        throw std::runtime_error("Failed to open file for reading");
    }

    EncodedData data;

    input.read(reinterpret_cast<char *>(&data.width), sizeof(data.width));
    input.read(reinterpret_cast<char *>(&data.height), sizeof(data.height));

    std::size_t size;
    input.read(reinterpret_cast<char *>(&size), sizeof(size));

    data.emptyIndexes.resize(size);
    for (std::size_t i = 0; i < size; ++i) {
        bool value;
        input.read(reinterpret_cast<char *>(&value), sizeof(bool));
        data.emptyIndexes[i] = value;
    }
    
    while (input.peek() != EOF) {
        unsigned char byte;
        input.read(reinterpret_cast<char *>(&byte), sizeof(byte));
        data.data.push_back(byte);
    }

    return data;
}
