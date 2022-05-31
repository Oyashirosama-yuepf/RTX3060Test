/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file extrinsic_io.h
 * @brief head for the extrinsic in/out
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2022-03-24
 */
#ifndef HOLO_CALIBRATION_IO_EXTRINSIC_IO_H_
#define HOLO_CALIBRATION_IO_EXTRINSIC_IO_H_

#include <holo/common/details/extrinsic.h>
#include <holo/io/common/extrinsic.h>

namespace holo
{
namespace calibration
{
namespace io
{
/**
 * @addtogroup io
 * @{
 *
 */
/**
 * @brief Load extrinsic from file
 *
 * @tparam T The data type, Scalar or Scalar_32
 * @param[in] filename Input path of extrinsic file
 *
 * @return ExtrinsicT<T>
 */
template <typename T>
holo::common::ExtrinsicT<T> LoadExtrinsic(std::string const& input_file_path)
{
    holo::yaml::Node const            node = holo::yaml::LoadFile(input_file_path);
    holo::common::ExtrinsicT<T> const pEc  = node.template as<holo::common::ExtrinsicT<T>>();

    return pEc;
}

/**
 * @brief Save extrinsic to file
 *
 * @tparam T The data type, Scalar or Scalar_32
 * @param[in] coordinates The coordinates of extrinsic, first is parent's, second is child's
 * @param[in] pTc Pose of child in parent coordinate
 * @param[in] output_file_path Output path of extrinsic file
 *
 * @return bool_t True, if success.
 */
template <typename T>
bool_t SaveExtrinsic(holo::common::Coordinate const& parent_coordinate,
                     holo::common::Coordinate const& child_coordinates, holo::geometry::Pose3T<T> const& pTc,
                     std::string const& output_file_path)
{
    std::ofstream ofile(output_file_path, std::ios::out);

    if (!ofile.is_open())
    {
        LOG(ERROR) << "Failed to open extrinsic file: " << output_file_path;
        return false;
    }

    holo::common::ExtrinsicT<T> const pEc(parent_coordinate, child_coordinates, pTc);
    holo::yaml::Node                  node;
    node = pEc;
    ofile << node;
    ofile.close();

    return true;
}
/**
 * @}
 */
}  // namespace io
}  // namespace calibration
}  // namespace holo

#endif  // HOLO_CALIBRATION_IO_EXTRINSIC_IO_H_
