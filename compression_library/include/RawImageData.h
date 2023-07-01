#pragma once

#include <vector>
#include <ostream>

struct RawImageData
{
    int width;
    int height;
    std::vector<unsigned char> data;

    /**
     * @brief Checks if the RawImageData is valid.
     *
     * The RawImageData is considered valid if the width and height are both greater than 0, and the data vector is not empty.
     *
     * @return true if the RawImageData is valid, false otherwise.
     */
    bool isValid() const
    {
        return width > 0 && height > 0 && !data.empty();
    }

    friend std::ostream& operator<<(std::ostream& os, const RawImageData& obj)
    {
        os << "RawImageData: width=" << obj.width << ", height=" << obj.height << ", data.size()=" << obj.data.size();

        for (int i = 0; i < obj.data.size(); i++)
        {
            if (i % obj.width == 0)
            {
                os << std::endl;
            }
            os << (int)obj.data[i] << " ";
        }

        return os;
    }
};
