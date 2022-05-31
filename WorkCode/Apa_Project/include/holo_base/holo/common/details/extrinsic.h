/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file extrinsic.h
 * @brief A class to held extrinsic parameters between coordinates (sensors)
 * @author lichao@holomatic.com
 * @author zhouhuishuang@holomatic.com
 * @date 2021-01-13
 */

#ifndef HOLO_COMMON_DETAILS_EXTRINSIC_H_
#define HOLO_COMMON_DETAILS_EXTRINSIC_H_

#include <holo/log/hololog.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include <holo/common/coordinate.h>
#include <holo/geometry/pose3.h>
#include <holo/utils/yaml.h>
#include <unistd.h>

namespace holo
{
namespace common
{
namespace details
{
/**
 * @brief This class to held extrinsic parameters between coordinates (sensors)
 */
template <typename Scalar>
class ExtrinsicT
{
public:
    using Pose3Type  = holo::geometry::Pose3T<Scalar>;
    using Coordinate = holo::common::Coordinate;
    using Matrix4f   = holo::numerics::Matrix4f;

    /**
     * @brief Construct a new Extrinsic T object
     *
     */
    ExtrinsicT() : parent_coordinate_{}, child_coordinate_{}, pose_{}
    {
    }

    /**
     * @brief Destroy the Extrinsic T object
     *
     */
    ~ExtrinsicT() noexcept
    {
    }

    /**
     * @brief Construct a new Extrinsic T object with multiple variables
     *
     * @param parent_frame parent coordinate
     * @param child_frame child coordinate
     * @param pose
     */
    ExtrinsicT(Coordinate parent_coordinate, Coordinate child_coordinate, const Pose3Type& pose)
    {
        parent_coordinate_ = parent_coordinate;
        child_coordinate_  = child_coordinate;
        pose_              = pose;
    }

    /**
     * @brief Get the Parent Coordinate object
     *
     * @return Coordinate
     */
    Coordinate GetParentCoordinate() const noexcept
    {
        return parent_coordinate_;
    }

    /**
     * @brief Set the Parent Coordinate object
     *
     * @param parent_coord
     */
    void SetParentCoordinate(const Coordinate parent_coord) noexcept
    {
        parent_coordinate_ = parent_coord;
    }

    /**
     * @brief Get the Child Coordinate object
     *
     * @return Coordinate
     */
    Coordinate GetChildCoordinate() const noexcept
    {
        return child_coordinate_;
    }

    /**
     * @brief Set the Child Coordinate object
     *
     * @param child_coord
     */
    void SetChildCoordinate(const Coordinate child_coord) noexcept
    {
        child_coordinate_ = child_coord;
    }

    /**
     * @brief Get the Pose object
     *
     * @return Pose3Type
     */
    Pose3Type GetPose() const noexcept
    {
        return pose_;
    }

    /**
     * @brief Set the Pose object
     *
     * @param pose the 3D pose
     */
    void SetPose(const Pose3Type& pose) noexcept
    {
        pose_ = pose;
    }

    SensorId GetSensorId() const noexcept
    {
        return child_coordinate_.GetVehicleSensorId();
    }

    /**
     * @brief convert to a string
     *
     * @return std::string
     */
    std::string ToString() const noexcept
    {
        const size_t      p = 6;
        const size_t      w = 15;
        std::stringstream ss;
        (void)ss.setf(std::ios_base::scientific, std::ios_base::floatfield);
        (void)std::setprecision(p);

        ss << "Extrinsic --- "
           << "\n"
           << "parent_frame_id: " << static_cast<uint32_t>(GetParentCoordinate()) << "\n"
           << "child_frame_id: " << static_cast<uint32_t>(GetChildCoordinate()) << std::endl;

        Matrix4f mat = GetPose().ToMatrix();

        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                ss << std::setw(w) << mat(i, j) << " ";
            }

            ss << std::setw(w) << mat(i, 3);

            if (i < 2)
            {
                ss << std::endl;
            }
        }

        return ss.str();
    }

    /**
     * @brief Save extrinsic to yaml file
     *
     * @param fn file name
     * @param ex extrinsic
     * @param verbose verbosity
     * @return true if success to save to yaml file
     * @return false if failed to save to yaml file
     */
    static bool SaveYaml(const std::string& fn, const ExtrinsicT& ex) noexcept
    {
        const size_t p = 12;

        holo::geometry::Quaternionf q(ex.GetPose().GetRotation().ToMatrix());

        yaml::Emitter emitter;
        (void)emitter.SetFloatPrecision(p);

        /* @todo use new coordinate type */
        emitter << yaml::BeginMap << yaml::Key << "x" << yaml::Value << ex.GetPose().GetX() << yaml::Key << "y"
                << yaml::Value << ex.GetPose().GetY() << yaml::Key << "z" << yaml::Value << ex.GetPose().GetZ()
                << yaml::Key << "qw" << yaml::Value << q.GetW() << yaml::Key << "qx" << yaml::Value << q.GetX()
                << yaml::Key << "qy" << yaml::Value << q.GetY() << yaml::Key << "qz" << yaml::Value << q.GetZ()
                << yaml::Key << "parent_coordinate" << yaml::Value << static_cast<uint32_t>(ex.GetParentCoordinate())
                << yaml::Key << "child_coordinate" << yaml::Value << static_cast<uint32_t>(ex.GetChildCoordinate());

        if (ex.GetChildCoordinate().GetType() == Coordinate::Type::VEHICLE)
        {
            emitter << yaml::Key << "sensor_id" << yaml::Value << static_cast<uint32_t>(ex.GetSensorId());
        }

        emitter << yaml::EndMap;

        std::ofstream out(fn.c_str());
        out << emitter.c_str();
        out.close();

        return true;
    }

    /**
     * @brief Load extrinsic from yaml file
     *
     * @param fn file name
     * @param verbose verbosity
     * @return Extrinsic loaded extrinsic file
     * @throws std::runtime_error if the file does not exist
     * @throws std::exception if parse node error
     */
    static ExtrinsicT LoadYaml(const std::string& fn)
    {
        if (access(fn.c_str(), R_OK) != 0)
        {
            std::stringstream ss;
            ss << fn << " dose not exist";
            throw std::runtime_error(ss.str());
        }

        Scalar     x = 0.0, y = 0.0, z = 0.0, qw = static_cast<Scalar>(1.0), qx = 0.0, qy = 0.0, qz = 0.0;
        Coordinate parent_coordinate;
        Coordinate child_coordinate;

        yaml::Node node_root = yaml::LoadFile(fn);

        x                 = node_root["x"].as<Scalar>();
        y                 = node_root["y"].as<Scalar>();
        z                 = node_root["z"].as<Scalar>();
        qw                = node_root["qw"].as<Scalar>();
        qx                = node_root["qx"].as<Scalar>();
        qy                = node_root["qy"].as<Scalar>();
        qz                = node_root["qz"].as<Scalar>();
        parent_coordinate = node_root["parent_coordinate"].as<uint32_t>();

        if (node_root["sensor_id"])
        {
            SensorId sid = node_root["sensor_id"].as<uint32_t>();
            child_coordinate.SetType(Coordinate::Type::VEHICLE);
            child_coordinate.SetVehicleSensorId(sid);
        }
        if (node_root["child_coordinate"])
        {
            child_coordinate = node_root["child_coordinate"].as<uint32_t>();
        }

        holo::geometry::Quaternionf q(qw, qx, qy, qz);

        holo::geometry::Rot3f   r(q.ToRotationMatrix());
        holo::geometry::Point3f t(x, y, z);

        /* @todo use new coordinate type in the future */
        ExtrinsicT ex(parent_coordinate, child_coordinate, holo::geometry::Pose3f(r, t));

        return ex;
    }

private:
    Coordinate parent_coordinate_;
    Coordinate child_coordinate_;
    Pose3Type  pose_;

}; /* class ExtrinsicT */

} /* namespace details */
} /* namespace common */
} /* namespace holo */
#endif /* HOLO_COMMON_DETAILS_EXTRINSIC_H_ */
