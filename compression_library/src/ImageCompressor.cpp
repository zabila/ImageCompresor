#include "ImageCompressor.h"
#include "Logger.h"
#include "ImageEncoder.h"
#include "ImageDecoder.h"

#include <fstream>
#include <BMPHeader.h>

std::shared_ptr<IEncoder> ImageCompressor::createEncoder()
{
    return std::make_shared<ImageEncoder>();
}

std::shared_ptr<IDecoder> ImageCompressor::createDecoder()
{
    return std::make_shared<ImageDecoder>();
}

void ImageCompressor::saveEncodedDataToFile(const std::string& filename, const EncodedData& data) const
{
    if (filename.substr(filename.find_last_of(".") + 1) != "barch")
    {
        throw std::runtime_error("Invalid file extension. Only .barch files are supported.");
    }

    std::ofstream output(filename, std::ios::binary);
    if (!output)
    {
        throw std::runtime_error("Failed to open file for writing");
    }

    output.write(reinterpret_cast<const char*>(&data.width), sizeof(data.width));
    output.write(reinterpret_cast<const char*>(&data.height), sizeof(data.height));

    std::size_t size = data.emptyIndexes.size();
    output.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const auto& index : data.emptyIndexes)
    {
        output.write(reinterpret_cast<const char*>(&index), sizeof(index));
    }

    for (const auto& byte : data.data)
    {
        output.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }
}

EncodedData ImageCompressor::loadEncodedDataFromFile(const std::string& filename) const
{
    if (filename.substr(filename.find_last_of(".") + 1) != "barch")
    {
        throw std::runtime_error("Invalid file extension. Only .barch files are supported.");
    }

    std::ifstream input(filename, std::ios::binary);
    if (!input)
    {
        throw std::runtime_error("Failed to open file for reading");
    }

    EncodedData data;

    input.read(reinterpret_cast<char*>(&data.width), sizeof(data.width));
    input.read(reinterpret_cast<char*>(&data.height), sizeof(data.height));

    std::size_t size;
    input.read(reinterpret_cast<char*>(&size), sizeof(size));

    data.emptyIndexes.resize(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        bool value;
        input.read(reinterpret_cast<char*>(&value), sizeof(bool));
        data.emptyIndexes[i] = value;
    }

    while (input.peek() != EOF)
    {
        unsigned char byte;
        input.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        data.data.push_back(byte);
    }

    return data;
}

void ImageCompressor::saveRawImageToFile(const std::string& filename, const RawImageData& imageData) const
{
    if (filename.substr(filename.find_last_of(".") + 1) != "bmp")
    {
        throw std::runtime_error("Invalid file extension. Only .bmp files are supported.");
    }

    std::ofstream file(filename, std::ios::binary);

    BMPHeader header;
    header.signature[0] = 'B';
    header.signature[1] = 'M';
    header.fileSize = sizeof(BMPHeader) + imageData.data.size();
    header.reserved = 0;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = sizeof(BMPHeader) - 14;
    header.width = imageData.width;
    header.height = imageData.height;
    header.planes = 1;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.dataSize = imageData.data.size();
    header.horizontalResolution = 0;
    header.verticalResolution = 0;
    header.colors = 0;
    header.importantColors = 0;

    file.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
    file.write(reinterpret_cast<const char*>(imageData.data.data()), imageData.data.size());
    file.close();
}

RawImageData ImageCompressor::loadRawImageFromFile(const std::string& filename) const
{
    if (filename.substr(filename.find_last_of(".") + 1) != "bmp")
    {
        throw std::runtime_error("Invalid file extension. Only .bmp files are supported.");
    }

    std::ifstream file(filename, std::ios::binary);

    int size = 0, pixels_adress = 0, width = 0, height = 0;
    short int bits_per_pixel = 0;
    file.seekg(2, std::ios::beg);
    file.read((char*)&size, sizeof(int));
    file.seekg(10, std::ios::beg);
    file.read((char*)&pixels_adress, sizeof(int));
    file.seekg(18, std::ios::beg);
    file.read((char*)&width, sizeof(int));
    file.read((char*)&height, sizeof(int));
    file.seekg(28, std::ios::beg);
    file.read((char*)&bits_per_pixel, sizeof(short int));
    file.seekg(pixels_adress, std::ios::beg);

    Log(INFO) << "Size:" << size;
    Log(INFO) << "pixels_adress:" << pixels_adress;
    Log(INFO) << "bits per pixel:" << bits_per_pixel;
    Log(INFO) << "Width:" << width;
    Log(INFO) << "Height:" << height;

    if (!file)
    {
        throw std::runtime_error("Failed to open file for reading");
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.signature[0] != 'B' || header.signature[1] != 'M')
    {
        throw std::runtime_error("Invalid file format");
        return {};
    }

    std::vector<unsigned char> imageData(header.dataSize);
    file.read(reinterpret_cast<char*>(imageData.data()), header.dataSize);

    file.close();

    RawImageData rawImageData;
    rawImageData.width = header.width;
    rawImageData.height = header.height;
    rawImageData.data = std::move(imageData);

    Log(INFO) << "Loaded file " << rawImageData;

    return rawImageData;
}
