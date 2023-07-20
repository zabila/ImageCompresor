#include "ImageEncoder.h"
#include "EncodedData.h"

#include <algorithm>
#include <stdexcept>

EncodedData ImageEncoder::encode(const RawImageData& rawImageData)
{
    if (!rawImageData.isValid()) {
        throw std::invalid_argument("Invalid raw image data");
    }

    EncodedData encodedData;
    encodedData.width = rawImageData.width;
    encodedData.height = rawImageData.height;

    const auto& data = rawImageData.data;
    const int totalRows = rawImageData.height;
    const int totalColumns = rawImageData.width;

    std::vector<char> encodedEmptyIndexes;
    encodedEmptyIndexes.reserve(totalRows);

    std::vector<unsigned char> encodedCompressedData;
    encodedCompressedData.reserve(totalRows * (totalColumns / COMPRESS_THRESHOLD));

    for (int currentRow = 0; currentRow < totalRows; ++currentRow) {
        const int rowIndexInData = currentRow * totalColumns;
        if (rowIndexInData >= data.size()) {
            throw std::out_of_range("Out of range error in raw image data");
        }

        const auto rowBegin = std::next(data.begin(), rowIndexInData);
        const auto rowEnd = std::next(rowBegin, totalColumns);

        const bool isEmptyRow = std::all_of(rowBegin, rowEnd, [](unsigned char pixel) { return pixel == WHITE; });
        encodedEmptyIndexes.push_back(isEmptyRow);
        if (isEmptyRow)
            continue;

        for (int currentColumn = 0; currentColumn < totalColumns; currentColumn += COMPRESS_THRESHOLD) {
            const auto groupBegin = std::next(rowBegin, currentColumn);
            const auto groupEnd = std::next(groupBegin, COMPRESS_THRESHOLD);

            if (std::all_of(groupBegin, groupEnd, [](unsigned char pixel) { return pixel == WHITE; })) {
                encodedCompressedData.push_back(0);
            } else if (std::all_of(groupBegin, groupEnd, [](unsigned char pixel) { return pixel == BLACK; })) {
                encodedCompressedData.push_back(10);
            } else {
                encodedCompressedData.push_back(11);
                encodedCompressedData.insert(encodedCompressedData.end(), groupBegin, groupEnd);
            }
        }
    }

    encodedData.emptyIndexes = std::move(encodedEmptyIndexes);
    encodedData.data = std::move(encodedCompressedData);

    return encodedData;
}
