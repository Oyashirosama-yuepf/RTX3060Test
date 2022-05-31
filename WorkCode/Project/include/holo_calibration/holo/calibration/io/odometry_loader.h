/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file odometry_loader.h
 * @brief define odometry loader
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2022-03-12
 */

#ifndef HOLO_CALIBRATION_IO_ODOMETRY_LOADER_H_
#define HOLO_CALIBRATION_IO_ODOMETRY_LOADER_H_

#include <string>
#include <vector>

#include <holo/common/odometry.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace calibration
{
namespace io
{
/**
 * @brief load matrix from yaml node
 *
 * @tparam T scalar type of the matrix
 * @tparam Row row of the matrix
 * @tparam Col column of the matrix
 * @param[in] node the given yaml node
 *
 * @return the loaded matrix
 */
template <typename T, uint16_t Row, uint16_t Col>
holo::numerics::MatrixBaseT<T, Row, Col> LoadMatrix(holo::yaml::Node const& node)
{
    holo::numerics::MatrixBaseT<T, Row, Col> result;

    if (node.size() != Row || (Col > 1u && node[0u].size() != Col))
    {
        LOG(ERROR) << "LoadMatrix --- the matrix size does not equal with yaml node size. matrix row*col = " << Row
                   << ", " << Col << ", yaml node row: " << node.size() << ", yaml node is: " << node;
        throw std::runtime_error("yaml node size does not meet required matrix size");
    }

    for (uint16_t row = 0u; row < result.GetRows(); row++)
    {
        for (uint16_t col = 0u; col < result.GetCols(); col++)
        {
            result(row, col) = Col > 1u ? node[row][col].as<T>() : node[row].as<T>();
        }
    }

    return result;
}

/**
 * @brief load odometry from yaml file
 *
 * @tparam T scalar type of the odometry
 * @param[in] filename the given yaml file
 *
 * @return the loaded odometry
 */
template <typename T>
std::vector<holo::common::OdometryT<T>> LoadYamlOdometry(std::string const& filename)
{
    std::vector<holo::common::OdometryT<T>> result;

    try
    {
        holo::yaml::Node const root = holo::yaml::LoadFile(filename);

        for (auto const& iter : root)
        {
            holo::yaml::Node const&    node = iter.second;
            holo::common::OdometryT<T> odometry;
            odometry.SetParentCoordinate(node["parent_coordinate"].as<uint32_t>());
            odometry.SetChildCoordinate(node["child_coordinate"].as<uint32_t>());
            odometry.SetTimestamp(holo::common::Timestamp(node["timestamp"]["sec"].as<uint32_t>(),
                                                          node["timestamp"]["nsec"].as<uint32_t>()));
            odometry.SetPrecisionFlags(node["precision"].as<uint32_t>());
            odometry.SetStatus(static_cast<typename holo::common::OdometryT<T>::Status>(node["status"].as<uint16_t>()));
            odometry.SetSource(static_cast<typename holo::common::OdometryT<T>::Source>(node["source"].as<uint16_t>()));
            holo::geometry::Rot3T<T> rot(LoadMatrix<T, 3u, 3u>(node["pose"]["rotation"]["matrix"]["data"]));
            holo::geometry::Point3T<T> trans(LoadMatrix<T, 3u, 1u>(node["pose"]["translation"]["data"]));
            odometry.SetPose(Pose3T<T>(rot, trans));
            odometry.SetPoseCovariance(LoadMatrix<T, 6u, 6u>(node["pose_covariance"]["data"]));
            odometry.SetVelocity(LoadMatrix<T, 6u, 1u>(node["velocity"]["data"]));
            odometry.SetVelocityCovariance(LoadMatrix<T, 6u, 6u>(node["velocity_covariance"]["data"]));
            odometry.SetLinearAcceleration(LoadMatrix<T, 3u, 1u>(node["linear_acceleration"]["data"]));
            result.push_back(odometry);
        }
    }
    catch (std::exception const& e)
    {
        LOG(ERROR) << "LoadYamlOdometry --- failed to load from yaml file: " << filename
                   << ", the exception is: " << e.what();
    }

    return result;
}

/**
 * @brief load odometry from csv file
 * @todo implement it if csv format is used lishuaijie@holomatic.com
 *
 * @tparam T scalar type of the odometry
 * @param[in] filename the given csv file
 *
 * @return the loaded odometry
 */
template <typename T>
std::vector<holo::common::OdometryT<T>> LoadCsvOdometry(std::string const& filename)
{
    (void)filename;
    LOG(ERROR) << "LoadCsvOdometry --- not implemented yet!!!";
    return std::vector<holo::common::OdometryT<T>>();
}

/**
 * @brief load odometry from file
 *
 * @tparam T scalar type of the odometry
 * @param[in] filename file name
 * @param[in] is_csv whether the format is csv
 *
 * @return the loaded odometry
 */
template <typename T>
std::vector<holo::common::OdometryT<T>> LoadOdometry(std::string const filename, bool_t const is_csv = false)
{
    std::vector<holo::common::OdometryT<T>> result;

    if (is_csv)
    {
        result = LoadCsvOdometry<T>(filename);
    }
    else
    {
        result = LoadYamlOdometry<T>(filename);
    }

    return result;
}

}  // namespace io
}  // namespace calibration
}  // namespace holo
#endif  // HOLO_CALIBRATION_IO_ODOMETRY_LOADER_H_
