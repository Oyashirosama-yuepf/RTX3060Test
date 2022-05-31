/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mat_io.h
 * @brief io stream for matrix
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2021-07-29
 */

#ifndef HOLO_CALIBRATION_IO_MAT_IO_H_
#define HOLO_CALIBRATION_IO_MAT_IO_H_

#include <fstream>
#include <string>

#include <holo/log/hololog.h>
#include <opencv2/imgproc.hpp>

#include <holo/core/types.h>

namespace holo
{
namespace calibration
{
namespace io
{
class MatIO
{
public:
    /**
     * @brief load a Mat from binary file
     *
     * @param[in] filename full file name of the binary file
     * @param[in][out] out the loaded Mat
     *
     * @return true -> success, false -> otherwise
     */
    static bool_t  LoadFromFile(std::string const& filename, cv::Mat& out);

    /**
     * @brief save Mat for binary file
     *
     * @param[in] in the Mat will be saved
     * @param[in] filename full file name of the binary file
     *
     * @return true -> success, false -> otherwise
     */
    static bool_t  SaveToFile(cv::Mat const& in, std::string const& filename);

    /**
     * @brief load a Mat from input stream
     *
     * @tparam ScalarType the scalar type of the Mat
     * @param[in] in input stream
     * @param[in][out] out the loaded Mat
     *
     * @return true -> success, false -> otherwise
     */
    template <typename ScalarType>
    static bool_t loadMat(std::istream& in, cv::Mat& out)
    {
        int32_t rows = 0;
        in.read(reinterpret_cast<char_t*>(&rows), sizeof(rows));
        int32_t cols = 0;
        in.read(reinterpret_cast<char_t*>(&cols), sizeof(cols));
        int32_t type = 0;
        in.read(reinterpret_cast<char_t*>(&type), sizeof(type));

        if (rows == 0 || cols == 0)
        {
            LOG(ERROR) << "MatIO --- invalid mat, rows = " << rows << ", cols = " << cols;
            return false;
        }

        out.create(rows, cols, type);
        int32_t channels = out.channels();

        for (int32_t row = 0; row < rows; row++)
        {
            for (int32_t col = 0; col < cols; col++)
            {
                ScalarType* ptr = out.ptr<ScalarType>(row, col);

                for (int32_t channel = 0; channel < channels; channel++)
                {
                    in.read(reinterpret_cast<char_t*>(ptr + channel), sizeof(ScalarType));
                }
            }
        }

        return true;
    }

    /**
     * @brief save a Mat ot output stream
     *
     * @tparam ScalarType the scalar type of the Mat
     * @param[in] in the Mat that will be saved
     * @param[in][out] out output stream
     *
     * @return true -> success, false -> otherwise
     */
    template <typename ScalarType>
    static bool_t saveMat(cv::Mat const& in, std::ostream& out)
    {
        int32_t const rows = in.rows;
        int32_t const cols = in.cols;
        int32_t const type = in.type();

        if (rows == 0 || cols == 0)
        {
            LOG(ERROR) << "MatIO --- invalid mat, rows = " << rows << ", cols = " << cols;
            return false;
        }

        out.write(reinterpret_cast<char_t const*>(&rows), sizeof(rows));
        out.write(reinterpret_cast<char_t const*>(&cols), sizeof(cols));
        out.write(reinterpret_cast<char_t const*>(&type), sizeof(type));

        int32_t channels = in.channels();

        for (int32_t row = 0; row < rows; row++)
        {
            for (int32_t col = 0; col < cols; col++)
            {
                ScalarType const* ptr = in.ptr<ScalarType>(row, col);

                for (int32_t channel = 0; channel < channels; channel++)
                {
                    out.write(reinterpret_cast<char_t const*>(ptr + channel), sizeof(ScalarType));
                }
            }
        }

        return true;
    }
};
}  // namespace io
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_IO_MAT_IO_H_
