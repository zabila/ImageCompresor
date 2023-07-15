#include "ImageEncoder.h"
#include "EncodedData.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

EncodedData ImageEncoder::encode(const RawImageData& raw_image_data)
{
    if (!raw_image_data.isValid())
        throw std::invalid_argument("Invalid raw image data");

    EncodedData encoded_data(raw_image_data);

    const std::vector<unsigned char>& raw_data = raw_image_data.data;
    const std::size_t total_row = raw_image_data.height;
    const std::size_t total_column = raw_image_data.width;

    std::vector<char> encoded_empty_row;
    encoded_empty_row.reserve(total_row);

    std::vector<unsigned char> encoded_compressed_data;
    encoded_compressed_data.reserve(total_row * (total_column / COMPRESS_THRESHOLD));

    for (std::size_t current_row = 0; current_row < total_row; ++current_row)
    {
        const int row_index_data = current_row * total_column;
        if (row_index_data >= raw_data.size())
            throw std::out_of_range("row_index_data out of range error in raw image data");

        const auto row_begin = std::next(raw_data.begin(), row_index_data);
        if (row_begin == raw_data.end())
            throw std::out_of_range("row_begin out of range error in raw image data");

        const auto row_end = std::next(row_begin, total_column);
        if (row_end == raw_data.end())
            throw std::out_of_range("row_data out of range error in raw image data");

        const bool is_empty_row = std::all_of(row_begin, row_end, [](unsigned char pixel) {
            return pixel == WHITE;
        });

        encoded_empty_row.push_back(is_empty_row);
        if (is_empty_row)
            continue;

        for (std::size_t current_column = 0; current_column < total_column; current_column += COMPRESS_THRESHOLD)
        {
            const auto group_begin = std::next(row_begin, current_column);
            if (group_begin == row_end)
                throw std::out_of_range("group_begin out of range error in raw image data");

            const auto group_end = std::next(group_begin, COMPRESS_THRESHOLD);
            if (group_end == row_end)
                throw std::out_of_range("group_begin out of range error in raw image data");

            const bool is_white_group = std::all_of(group_begin, group_end, [](unsigned char pixel) {
                return pixel == WHITE;
            });
            if (is_white_group)
            {
                encoded_compressed_data.push_back(0);
                continue;
            }

            const bool is_black_group = std::all_of(group_begin, group_end, [](unsigned char pixel) {
                return pixel == BLACK;
            });
            if (is_black_group)
            {
                encoded_compressed_data.push_back(10);
                continue;
            }

            encoded_compressed_data.push_back(11);
            encoded_compressed_data.insert(encoded_compressed_data.end(), group_begin, group_end);
        }
    }

    encoded_data.emptyIndexes = std::move(encoded_empty_row);
    encoded_data.data = std::move(encoded_compressed_data);

    return encoded_data;
}
