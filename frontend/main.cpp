#include "CompressorFactory.h"
#include "EncodedData.h"
#include "ICompressor.h"
#include "ImageEncoder.h"
#include "ImageDecoder.h"
#include "RawImageData.h"

#include <memory>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        std::vector<unsigned char> imageData{0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};
        RawImageData image{12, 1, imageData};

        CompressorFactory factory;
        std::shared_ptr<ICompressor> compressor = factory.createCompressor();
        std::shared_ptr<IEncoder> encoder = compressor->createEncoder();
        std::shared_ptr<IDecoder> decoder = compressor->createDecoder();

        EncodedData encodedData = encoder->encode(image);
        RawImageData decodedImage = decoder->decode(encodedData);

        compressor->saveToFile("test.barch", encodedData);
        EncodedData loadedData = compressor->loadFromFile("test.barch");

        RawImageData decodedFromFile = decoder->decode(loadedData);

        std::cout << "End!";
    }
    catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << '\n';
        return 1;  // Indicate failure
    }

    return 0;
}