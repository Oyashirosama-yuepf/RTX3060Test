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

#ifndef HOLO_MAP_PARKING_NAVIGATION_H_
#define HOLO_MAP_PARKING_NAVIGATION_H_

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
namespace map
{

/**
 * @brief parking navigation frame.
 *
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnUkyXLn38iWYIw5Kc91Gmub
 */

template <typename T>
class ParkingNavigationPointT
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
        return (sizeof(int32_t) * 3) +
               holo::serialization::SerializedSize<ALIGN>(left_available_width_, right_available_width_,
                                                          left_extend_area_width_, right_extend_area_width_, status_,
                                                          curvature_radius_, slope_, horizontal_slope_, theta_);
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
                   << horizontal_slope_ << theta_;
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
            left_extend_area_width_ >> right_extend_area_width_ >> status_ >> curvature_radius_ >> slope_ >>
            horizontal_slope_ >> theta_;
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
    holo::bool_t const GetCurvatureFlag() const
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
     * @brief Get horizontal SlopeFlag
     *
     * @return true:  horizontal slope valid
     *         false: horizontal slope Invalid
     */
    holo::bool_t const GetHorizontalSlopeFlag() const
    {
        return this->horizontal_slope_flag_;
    }

    /**
     * @brief Get horizontal slope(Unit: radian).
     *
     * @return A horizontal slope value.
     */
    ScalarType const GetHorizontalSlope() const
    {
        return this->horizontal_slope_;
    }

    /**
     * @brief Get SlopeFlag
     *
     * @return true:  slope valid
     *         false: slope Invalid
     */
    holo::bool_t const GetSlopeFlag() const
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

    uint16_t GetStatus() const
    {
        return status_;
    }

    void SetStatus(uint16_t status)
    {
        this->status_ = status;
    }

private:
    PointType ref_point_;                    ///< Ref point.
    uint16_t  left_available_width_    = 0;  ///< Unit: cm.
    uint16_t  right_available_width_   = 0;  ///< Unit: cm.
    uint16_t  left_extend_area_width_  = 0;  ///< Unit: cm.
    uint16_t  right_extend_area_width_ = 0;  ///< Unit: cm.
    float32_t curvature_radius_        = 0;  ///< Unit: meter.
    float32_t slope_                   = 0;  ///< Unit: radian.
    float32_t horizontal_slope_        = 0;  ///< Unit: radian.
    float32_t theta_                   = 0;  ///< Unit: radian.

    union
    {
        uint16_t status_ = 0;
        struct
        {
            bool_t curvature_flag_ : 1;         ///< curvature flag
            bool_t slope_flag_ : 1;             ///< slope flag exist
            bool_t horizontal_slope_flag_ : 1;  ///< horizontal slope exist
        };
    };
};

template <typename T, size_t SIZE = std::numeric_limits<size_t>::max()>
class ParkingNavigationT : public holo::container::details::VectorBase<ParkingNavigationPointT<T>, SIZE>
{
public:
    using ScalarType          = T;
    using NavigationPointType = ParkingNavigationPointT<T>;
    using Base                = holo::container::details::VectorBase<NavigationPointType, SIZE>;
    using CoordinateType      = holo::common::Coordinate;

    /**
     * @brief Get the Coordinate object
     *
     * @return Coordinate coordinate
     */
    CoordinateType GetCoordinate() const noexcept
    {
        return this->coordinate_;
    }

    /**
     * @brief Set the Coordinate object
     *
     * @param coordiante coordinate
     */
    void SetCoordinate(CoordinateType const& coordinate) noexcept
    {
        this->coordinate_ = coordinate;
    }

    /**
     * @brief Get the Timestamp object
     *
     * @return Timestamp timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set the Timestamp object
     *
     * @param timestamp timestamp
     */
    void SetTimestamp(Timestamp const& timestamp) noexcept
    {
        timestamp_ = timestamp;
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
        size_t aligned_size = timestamp_.GetSerializedSize<ALIGN>() +
                              holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_),
                                                                         static_cast<uint32_t>(this->size()));
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
        serializer << timestamp_ << static_cast<uint32_t>(coordinate_) << static_cast<uint32_t>(this->size());
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
        uint32_t coord;
        uint32_t size;
        deserializer >> timestamp_ >> coord >> size;
        coordinate_ = coord;
        this->resize(size);
        for (auto& ps : (*this))
        {
            deserializer >> ps;
        }
    }
private:
    Timestamp  timestamp_;       ///< timestamp
    CoordinateType coordinate_;  ///< coordinate
};

using ParkingNavigationf = ParkingNavigationT<float32_t>;
using ParkingNavigationd = ParkingNavigationT<float64_t>;
using ParkingNavigation  = ParkingNavigationd;

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_PARKING_NAVIGATION_H_ */
