#include "ImageEncoder.h"
#include "EncodedData.h"

#include <algorithm>
#include <stdexcept>

EncodedData ImageEncoder::encode(const RawImageData& raw_image_data)
{
    if (!raw_image_data.is_valid()) {
        throw std::invalid_argument("Invalid raw image data");
    }

    EncodedData encoded_data;
    encoded_data.width = raw_image_data.width;
    encoded_data.height = raw_image_data.height;

    const auto& row_data = raw_image_data.data;
    const int total_row = raw_image_data.height;
    const int total_column = raw_image_data.width;

    std::vector<char> encoded_empty_indexes;
    encoded_empty_indexes.reserve(total_row);

    std::vector<unsigned char> encoded_compressed_data;
    encoded_compressed_data.reserve(total_row * (total_column / COMPRESS_THRESHOLD));

    for (int current_row = 0; current_row < total_row; ++current_row) {
        const int row_index_in_data = current_row * total_column;
        if (row_index_in_data >= row_data.size()) {
            throw std::out_of_range("Out of range error in raw image data");
        }

        const auto row_begin = std::next(row_data.begin(), row_index_in_data);
        const auto row_end = std::next(row_begin, total_column);

        const bool is_empty_row = std::all_of(row_begin, row_end, [](unsigned char pixel) { return pixel == WHITE; });
        encoded_empty_indexes.push_back(is_empty_row);
        if (is_empty_row)
            continue;

        for (int current_colum = 0; current_colum < total_column; current_colum += COMPRESS_THRESHOLD) {
            const auto group_begin = std::next(row_begin, current_colum);
            const auto group_end = std::next(group_begin, COMPRESS_THRESHOLD);

            if (std::all_of(group_begin, group_end, [](unsigned char pixel) { return pixel == WHITE; })) {
                encoded_compressed_data.push_back(0);
            } else if (std::all_of(group_begin, group_end, [](unsigned char pixel) { return pixel == BLACK; })) {
                encoded_compressed_data.push_back(10);
            } else {
                encoded_compressed_data.push_back(11);
                encoded_compressed_data.insert(encoded_compressed_data.end(), group_begin, group_end);
            }
        }
    }

    encoded_data.emptyIndexes = std::move(encoded_empty_indexes);
    encoded_data.data = std::move(encoded_compressed_data);

    return encoded_data;
}
