#include "ImageDecoder.h"

#include <stdexcept>
#include <vector>

RawImageData ImageDecoder::decode(const EncodedData& encoded_data)
{
    RawImageData raw_image_data;
    raw_image_data.width = encoded_data.width;
    raw_image_data.height = encoded_data.height;

    const auto& encoded_empty_indexes = encoded_data.emptyIndexes;
    const auto& encoded_compress_data = encoded_data.data;
    const int total_row = encoded_data.height;
    const int total_collum = encoded_data.width;

    auto encodedDataIterator = encoded_compress_data.begin();

    for (int currentRow = 0; currentRow < total_row; ++currentRow)
    {
        if (encoded_empty_indexes[currentRow])
        {
            for (int i = 0; i < total_collum; ++i)
            {
                raw_image_data.data.push_back(WHITE);
            }
            continue;
        }

        for (int currentColumn = 0; currentColumn < total_collum; currentColumn += COMPRESS_THRESHOLD)
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

            raw_image_data.data.insert(raw_image_data.data.end(), group.begin(), group.end());
        }
    }

    return raw_image_data;
}
