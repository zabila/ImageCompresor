#include "ImageDecoder.h"

#include <stdexcept>
#include <vector>

RawImageData ImageDecoder::decode(const EncodedData& encodedData)
{
    RawImageData rawImageData;
    rawImageData.width = encodedData.width;
    rawImageData.height = encodedData.height;

    const auto& encodedEmptyIndexes = encodedData.emptyIndexes;
    const auto& encodedCompressedData = encodedData.data;
    const int totalRows = encodedData.height;
    const int totalColumns = encodedData.width;

    auto encodedDataIterator = encodedCompressedData.begin();

    for (int currentRow = 0; currentRow < totalRows; ++currentRow)
    {
        if (encodedEmptyIndexes[currentRow])
        {
            for (int i = 0; i < totalColumns; ++i)
            {
                rawImageData.data.push_back(WHITE);
            }
            continue;
        }

        for (int currentColumn = 0; currentColumn < totalColumns; currentColumn += COMPRESS_THRESHOLD)
        {
            unsigned char encodedGroup = *encodedDataIterator++;
            std::vector<unsigned char> group;
            if (encodedGroup == 0)
            {
                group = std::vector<unsigned char>(COMPRESS_THRESHOLD, WHITE);
            }
            else if (encodedGroup == 10)
            {
                group = std::vector<unsigned char>(COMPRESS_THRESHOLD, BLACK);
            }
            else if (encodedGroup == 11)
            {
                group = std::vector<unsigned char>(encodedDataIterator, encodedDataIterator + COMPRESS_THRESHOLD);
                std::advance(encodedDataIterator, COMPRESS_THRESHOLD);
            }
            else
            {
                throw std::invalid_argument("Invalid encoded group value");
            }

            rawImageData.data.insert(rawImageData.data.end(), group.begin(), group.end());
        }
    }

    return rawImageData;
}
