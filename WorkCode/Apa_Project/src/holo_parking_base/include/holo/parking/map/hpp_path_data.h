/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_navigation.h
 * @brief Define parking navigation road frame
 * @author wangminghui@holomatic.com
 * @date "2021-11-04"
 */

#ifndef HOLO_PARKING_MAP_HPP_PATH_DATA_H_
#define HOLO_PARKING_MAP_HPP_PATH_DATA_H_

#include <holo/common/coordinate.h>
#include <holo/common/road_type.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/vector.h>
#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/curve.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>

#include <cmath>
#include <limits>
#include <utility>
#include <vector>

namespace holo
{
namespace parking
{
namespace map
{
/**
 * @brief parking hpp path frame.
 *
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnfJb1Fyov3IvmKnQlF5bpHb#
 */

template <typename T>
class ParkingPointT
{
public:
    using ScalarType = T;
    using PointType  = holo::geometry::Point3T<T>;

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @param ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return (sizeof(int32_t) * 3) + holo::serialization::SerializedSize<ALIGN>(
                                           left_available_width_, right_available_width_, left_extend_area_width_,
                                           right_extend_area_width_, status_, curvature_radius_, slope_, theta_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::exception::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        // ref_point_ conversion to integer transmission,keep Two decimal
        int32_t point_x = ref_point_.GetX() * 100;
        int32_t point_y = ref_point_.GetY() * 100;
        int32_t point_z = ref_point_.GetZ() * 100;
        serializer << point_x << point_y << point_z << left_available_width_ << right_available_width_
                   << left_extend_area_width_ << right_extend_area_width_ << status_ << curvature_radius_ << slope_
                   << theta_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        int32_t point_x = 0;
        int32_t point_y = 0;
        int32_t point_z = 0;
        // ref_point_ conversion to integer transmission,keep Two decimal
        deserializer >> point_x >> point_y >> point_z >> left_available_width_ >> right_available_width_ >>
            left_extend_area_width_ >> right_extend_area_width_ >> status_ >> curvature_radius_ >> slope_ >> theta_;
        ref_point_.Set(point_x / 100.0, point_y / 100.0, point_z / 100.0);
    }

    /**
     * @brief Set ref point.
     *
     * @param[in] ref_point A new point value.
     */
    void SetRefPoint(PointType const& ref_point)
    {
        this->ref_point_ = ref_point;
    }

    /**
     * @brief get x
     *
     * @return ScalarType
     */
    ScalarType const GetX() const
    {
        return this->ref_point_.GetX();
    }

    /**
     * @brief set x
     *
     * @param x value
     */
    void SetX(ScalarType const& x)
    {
        this->ref_point_.SetX(x);
    }

    /**
     * @brief get y
     *
     * @return ScalarType
     */
    ScalarType const GetY() const
    {
        return this->ref_point_.GetY();
    }

    /**
     * @brief set y
     *
     * @param y value
     */
    void SetY(ScalarType const& y)
    {
        this->ref_point_.SetY(y);
    }

    /**
     * @brief set z
     *
     * @param z value
     */
    void SetZ(ScalarType const& z) noexcept
    {
        this->ref_point_.SetZ(z);
    }

    /**
     * @brief get z
     *
     * @return ScalarType
     */
    ScalarType const GetZ() const
    {
        return this->ref_point_.GetZ();
    }

    /**
     * @brief Set ref point.
     *
     * @param[in] x A new point.x value.
     * @param[in] y A new point.y value.
     * @param[in] z A new point.z value.
     */
    void SetRefPoint(ScalarType const& x, ScalarType const& y, ScalarType const& z)
    {
        this->ref_point_.Set(x, y, z);
    }

    /**
     * @brief Get ref point.
     *
     * @return A reference of PointType object.
     */
    PointType const& GetRefPoint() const
    {
        return this->ref_point_;
    }

    /**
     * @brief Get left extend area width (Unit:cm)
     * @return A current point left extend area width value
     */
    ScalarType const GetLeftExtendAreaWidth() const
    {
        return this->left_extend_area_width_;
    }

    /**
     * @brief Set left extend area width
     *
     * @param[in] value A new ScalarType value.
     */
    void SetLeftExtendAreaWidth(ScalarType const& value)
    {
        this->left_extend_area_width_ = value;
    }

    /**
     * @brief Get right extend area width (Unit:cm)
     * @return A current point right extend area width value
     */
    ScalarType const GetRightExtendAreaWidth() const
    {
        return this->right_extend_area_width_;
    }

    /**
     * @brief Set right extend area width
     *
     * @param[in] value A new ScalarType value.
     */
    void SetRightExtendAreaWidth(ScalarType const& value)
    {
        this->right_extend_area_width_ = value;
    }

    /**
     * @brief Set left area width
     *
     * @param[in] value A new ScalarType value.
     */
    void SetLeftAvailableWidth(ScalarType const& value)
    {
        this->left_available_width_ = value;
    }

    /**
     * @brief Get left area width (Unit:cm)
     * @return A current point left area width value
     */
    ScalarType const GetLeftAvailableWidth() const
    {
        return this->left_available_width_;
    }

    /**
     * @brief Set right extend area width
     *
     * @param[in] value A new ScalarType value.
     */
    void SetRightAvailableWidth(ScalarType const& value)
    {
        this->right_available_width_ = value;
    }

    /**
     * @brief right area width(Unit:cm)
     * @return A current point right area width value
     */
    ScalarType const GetRightAvailableWidth() const
    {
        return this->right_available_width_;
    }

    /**
     * @brief Get CurvatureFlag
     *
     * @return true: curvature valid
     *         false: curvature Invalid
     */
    holo::bool_t GetCurvatureFlag()
    {
        return this->curvature_flag_;
    }

    /**
     * @brief Set curvature radius (Unit: meter).
     *
     * @param[in] curvature A curvature radius value.
     */
    void SetCurvatureRadius(ScalarType const& curvature_radius) noexcept
    {
        this->curvature_radius_ = curvature_radius;
    }

    /**
     * @brief Get curvature radius (Unit: meter).
     *
     * @return A curvature radius value.
     */
    ScalarType const GetCurvatureRadius() const
    {
        return this->curvature_radius_;
    }

    /**
     * @brief Get SlopeFlag
     *
     * @return true:  slope valid
     *         false: slope Invalid
     */
    holo::bool_t GetSlopeFlag()
    {
        return this->slope_flag_;
    }

    /**
     * @brief Set slope(Unit: radian).
     *
     * @param[in] slope A new slope value.
     */
    void SetSlope(ScalarType const& slope)
    {
        this->slope_ = slope;
    }

    /**
     * @brief Get slope(Unit: radian).
     *
     * @return A slope value.
     */
    ScalarType const GetSlope() const
    {
        return this->slope_;
    }

    /**
     * @brief Set slope(Unit: radian).
     *
     * @param[in] slope A new slope value.
     */
    void SetTheta(ScalarType const& theta)
    {
        this->theta_ = theta;
    }

    /**
     * @brief Get Theta(Unit: radian).
     *
     * @return A theta value.
     */
    ScalarType const GetTheta() const
    {
        return this->theta_;
    }
    template <typename NavigationPoint>
    NavigationPoint ToNavigationPoint()
    {
        NavigationPoint navigation_point;
        navigation_point.SetRefPoint(GetRefPoint());
        navigation_point.SetLeftAvailableWidth(left_available_width_);
        navigation_point.SetRightAvailableWidth(right_available_width_);
        navigation_point.SetLeftExtendAreaWidth(left_extend_area_width_);
        navigation_point.SetRightExtendAreaWidth(right_extend_area_width_);
        navigation_point.SetCurvatureRadius(curvature_radius_);
        navigation_point.SetSlope(slope_);
        navigation_point.SetTheta(theta_);
        return navigation_point;
    }

private:
    PointType ref_point_;                    ///< Ref point.
    uint16_t  left_available_width_    = 0;  ///< Unit: cm.
    uint16_t  right_available_width_   = 0;  ///< Unit: cm.
    uint16_t  left_extend_area_width_  = 0;  ///< Unit: cm.
    uint16_t  right_extend_area_width_ = 0;  ///< Unit: cm.
    float32_t curvature_radius_        = 0;  ///< Unit: meter.
    float32_t slope_                   = 0;  ///< Unit: radian.
    float32_t theta_                   = 0;  ///< Unit: radian.

    union
    {
        uint16_t status_ = 0;
        struct
        {
            bool_t curvature_flag_ : 1;  ///< curvature flag
            bool_t slope_flag_ : 1;      ///< slope flag exist
        };
    };
};

template <typename T, size_t SIZE = std::numeric_limits<size_t>::max()>
class ParkingLaneT : public holo::container::details::VectorBase<ParkingPointT<T>, SIZE>
{
public:
    using ScalarType          = T;
    using NavigationPointType = ParkingPointT<T>;
    using Base                = holo::container::details::VectorBase<NavigationPointType, SIZE>;
    using CoordinateType      = holo::common::Coordinate;
    enum class LaneDir : holo::uint8_t
    {
        LANE_DIR_UNDEFINED          = 0,
        LANE_DIR_POSITIVE_DIRECTION = 1,
        LANE_DIR_NEGATIVE_DIRECTION = 2,
    };
    /**
     * @brief Get the Coordinate object
     *
     * @return Coordinate coordinate
     */
    CoordinateType GetCoordinate() const noexcept
    {
        return this->lane_coordinate_;
    }

    /**
     * @brief Set the Coordinate object
     *
     * @param coordiante coordinate
     */
    void SetCoordinate(CoordinateType const& coordinate) noexcept
    {
        this->lane_coordinate_ = coordinate;
    }

    ::std::uint64_t GetLaneId() const
    {
        return lane_id_;
    }

    void SetLaneId(const ::std::uint64_t _lane_id)
    {
        lane_id_ = _lane_id;
    }
    const LaneDir& GetLaneDir() const
    {
        return lane_dir_;
    }
    void SetLaneDir(const LaneDir& _lane_dir)
    {
        lane_dir_ = _lane_dir;
    }

    ::std::uint32_t GetLaneLength() const
    {
        return lane_length_;
    }

    void SetLaneLength(const ::std::uint32_t lane_length)
    {
        lane_length_ = lane_length;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return Base::template GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   static_cast<uint64_t>(lane_id_), static_cast<holo::uint8_t>(lane_dir_),
                   static_cast<uint32_t>(lane_length_), static_cast<uint32_t>(lane_coordinate_));
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        Base::template Serialize(serializer);
        serializer << lane_id_ << static_cast<holo::uint8_t>(lane_dir_) << lane_length_ << lane_coordinate_
                   << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        Base::template Deserialize(deserializer);
        holo::uint8_t lane_dir;
        deserializer >> lane_id_ >> lane_dir >> lane_length_ >> lane_coordinate_ >> holo::serialization::align;
        lane_dir_ = static_cast<LaneDir>(lane_dir);
    }

private:
    holo::uint64_t lane_id_;
    LaneDir        lane_dir_;
    holo::uint32_t lane_length_;      // Unit:cm
    CoordinateType lane_coordinate_;  ///< coordinate
};

template <typename T, size_t SIZE = std::numeric_limits<size_t>::max()>
class ParkingPathT : public holo::container::details::VectorBase<ParkingLaneT<T>, SIZE>
{
public:
    using ScalarType = T;
    using PointType  = ParkingPointT<T>;
    using LaneType   = ParkingLaneT<T>;
    using Base       = holo::container::details::VectorBase<LaneType, SIZE>;

    holo::uint64_t GetPathId() const
    {
        return path_id_;
    }

    void SetPathId(const holo::uint64_t path_id)
    {
        path_id_ = path_id;
    }

    holo::uint32_t GetVersionCode() const
    {
        return version_code_;
    }

    void SetVersionCode(const holo::uint32_t version_code)
    {
        version_code_ = version_code;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        size_t aligned_size = holo::serialization::SerializedSize<ALIGN>(
            static_cast<uint64_t>(path_id_), static_cast<uint32_t>(version_code_), static_cast<uint32_t>(this->size()));
        for (auto const& ps : (*this))
        {
            aligned_size += ps.template GetSerializedSize<ALIGN>();
        }
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::exception::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << static_cast<uint64_t>(path_id_) << static_cast<uint32_t>(version_code_)
                   << static_cast<uint32_t>(this->size());
        for (auto const& ps : (*this))
        {
            serializer << ps;
        }
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t size;
        deserializer >> path_id_ >> version_code_ >> size;
        this->resize(size);
        for (auto& ps : (*this))
        {
            deserializer >> ps;
        }
    }

private:
    holo::uint64_t path_id_;
    holo::uint32_t version_code_;
};

using ParkingPathf = ParkingPathT<float32_t>;
using ParkingPathd = ParkingPathT<float64_t>;
using ParkingPath  = ParkingPathd;

}  // namespace map
}  // namespace parking
}  // namespace holo

#endif /* HOLO_PARKING_MAP_HPP_PATH_DATA_H_ */
