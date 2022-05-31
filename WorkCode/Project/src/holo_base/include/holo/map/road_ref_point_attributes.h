/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_ref_point_attributes.h
 * @brief Define road attributes message info
 * @author lisong@holomatic.com
 * @date "2020-08-04"
 */

#ifndef HOLO_MAP_ROAD_REF_POINT_ATTRIBUTES_H_
#define HOLO_MAP_ROAD_REF_POINT_ATTRIBUTES_H_

#include <cmath>
#include <limits>
#include <utility>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/common/road_category.h>
#include <holo/common/road_type.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/vector.h>
#include <holo/core/epsilon.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief Slope\curvature_radius\superelevation of road.
 *
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnxymWmsPSdPBdcnEQfe362b
 */
class RoadScs
{
public:
    using ScalarType = holo::float32_t;

    /**
     * @brief Default constructer
     */
    RoadScs() = default;

    /**
     * @brief Constructer with parameters
     *
     * @param[in] distance Distance from this road attribute to car position, unit: meter
     * @param[in] slope Slope, unit: radian
     * @param[in] curvature_radius Curvature radius, unit: meter
     * @param[in] superelevation Superelevation, unit: radian
     */
    RoadScs(ScalarType const distance, ScalarType const slope, ScalarType const curvature_radius,
            ScalarType const superelevation) noexcept
      : distance_(distance), slope_(slope), curvature_radius_(curvature_radius), superelevation_(superelevation)

    {
    }

    /**
     * @brief Get distance(Unit: meter).
     *
     * @return A distance value.
     */
    ScalarType GetDistance() const noexcept
    {
        return this->distance_;
    }

    /**
     * @brief Set distance(Unit: meter).
     *
     * @param[in] distance A distance value.
     * @return Nothing.
     */
    void SetDistance(ScalarType const distance) noexcept
    {
        this->distance_ = distance;
    }

    /**
     * @brief Get slope(Unit: radian).
     *
     * @return A slope value.
     */
    ScalarType GetSlope() const noexcept
    {
        return this->slope_;
    }

    /**
     * @brief Set slope(Unit: radian).
     *
     * @param[in] slope A new slope value.
     * @return Nothing
     */
    void SetSlope(ScalarType const slope) noexcept
    {
        this->slope_ = slope;
    }

    /**
     * @brief Get curvature radius (Unit: meter).
     *
     * @return A curvature radius value.
     */
    ScalarType GetCurvatureRadius() const noexcept
    {
        return curvature_radius_;
    }

    /**
     * @brief Set curvature radius (Unit: meter).
     *
     * @param[in] curvature A curvature radius value.
     * @return Nothong.
     */
    void SetCurvatureRadius(ScalarType const curvature_radius) noexcept
    {
        this->curvature_radius_ = curvature_radius;
    }

    /**
     * @brief Get superelevation(Unit: radian).
     *
     * @return A super elevation value.
     */
    ScalarType GetSuperelevation() const noexcept
    {
        return this->superelevation_;
    }

    /**
     * @brief Set superelevation(Unit: radian).
     *
     * @param [in] superelevation
     * @return Nothing.
     */
    void SetSuperelevation(ScalarType const superelevation) noexcept
    {
        this->superelevation_ = superelevation;
    }

    /**
     * @brief == operator.
     *
     * @param [in] other A RoadScs object
     * @return True if equal.
     * @return False if not equal.
     */
    holo::bool_t operator==(RoadScs const& other) const noexcept
    {
        return ScalarEqualT<ScalarType>()(distance_, other.distance_) &&
               ScalarEqualT<ScalarType>()(slope_, other.slope_) &&
               ScalarEqualT<ScalarType>()(curvature_radius_, other.curvature_radius_) &&
               ScalarEqualT<ScalarType>()(superelevation_, other.superelevation_);
    }

    template <size_t ALIGN = 4U>
    std::size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(distance_, slope_, curvature_radius_, superelevation_);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << distance_ << slope_ << curvature_radius_ << superelevation_
                   << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> distance_ >> slope_ >> curvature_radius_ >> superelevation_ >>
            holo::serialization::align;
    }

private:
    ScalarType distance_         = 0.0f;  ///< Distance to ref point, unit: meter.
    ScalarType slope_            = 0.0f;  ///< Unit: radian.
    ScalarType curvature_radius_ = 0.0f;  ///< Unit: meter.
    ScalarType superelevation_   = 0.0f;  ///< Unit: radian.
};                                        // RoadScs

/**
 * @brief Road type interval of road.
 *
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnxymWmsPSdPBdcnEQfe362b
 */
class RoadTypeInterval
{
public:
    using IntervalType = std::pair<holo::float32_t, holo::float32_t>;

    /**
     * @brief Default constructer
     */
    RoadTypeInterval() = default;

    /**
     * @brief Constructer with parameters
     *
     * @param[in] interval Interval of road type
     * @param[in] road_type Road type of this road type interval
     */
    [[deprecated]] RoadTypeInterval(IntervalType const& interval, holo::common::RoadType const& road_type) noexcept
      : interval_(interval)
    {
        road_category_.SetValue(road_type.GetValue());
    }

    /**
     * @brief Constructer with parameters
     *
     * @param[in] interval Interval of road type
     * @param[in] road_category Road category of this road type interval
     */
    RoadTypeInterval(IntervalType const& interval, holo::common::RoadCategory const& road_category) noexcept
      : interval_(interval), road_category_(road_category)
    {
    }

    /**
     * @brief Get road interval.
     *
     * @return A const reference of IntervalType object.
     */
    IntervalType const& GetInterval() const noexcept
    {
        return this->interval_;
    }

    /**
     * @brief Get road interval.
     *
     * @return A const reference of IntervalType object.
     */
    IntervalType& GetInterval() noexcept
    {
        return this->interval_;
    }

    /**
     * @brief Set road interval.
     *
     * @param[in] interval A road interval
     * @return Nothing.
     */
    void SetInterval(IntervalType const& interval) noexcept
    {
        this->interval_ = interval;
    }

    /**
     * @brief Get road type.
     *
     * @deprecated Deprecated soon, please use GetRoadCategory()
     */
    [[deprecated]] holo::common::RoadType const& GetRoadType() const {
        throw std::runtime_error("RoadTypeInterval --- calling unimplemented function.");
    }

    /**
     * @brief Get road Category.
     *
     * @return A const reference of holo::common::RoadCategory object.
     */
    holo::common::RoadCategory const& GetRoadCategory() const noexcept
    {
        return this->road_category_;
    }

    /**
     * @brief Get road type.
     *
     * @deprecated Deprecated soon, please use GetRoadCategory()
     *
     * @return A const reference of holo::common::RoadType object.
     */
    [[deprecated]] holo::common::RoadType& GetRoadType() {
        throw std::runtime_error("RoadTypeInterval --- calling unimplemented function.");
    }

    /**
     * @brief Get road category.
     *
     * @return A const reference of holo::common::RoadCategory object.
     */
    holo::common::RoadCategory& GetRoadCategory() noexcept
    {
        return this->road_category_;
    }

    /**
     * @brief Set road type.
     *
     * @deprecated Deprecated soon, please use SetRoadCategory(RoadCategory const& road_category)
     *
     * @param[in] road_type A holo::common::RoadType object
     * @return Nothing.
     */
    [[deprecated]] void SetRoadType(holo::common::RoadType const& road_type) noexcept
    {
        this->road_category_.SetValue(road_type.GetValue());
    }

    /**
     * @brief Set road category.
     *
     * @param[in] road_category A holo::common::RoadCategory object
     * @return Nothing.
     */
    void SetRoadCategory(holo::common::RoadCategory const& road_category) noexcept
    {
        this->road_category_ = road_category;
    }

    /**
     * @brief == operator.
     *
     * @param [in] other A RoadTypeInterval object
     * @return True if equal.
     * @return False if not equal.
     */
    holo::bool_t operator==(RoadTypeInterval const& other) const noexcept
    {
        return (interval_ == other.interval_) && (road_category_ == other.road_category_);
    }

    template <size_t ALIGN = 4U>
    std::size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(interval_.first, interval_.second,
                                                          static_cast<uint32_t>(road_category_));
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << holo::serialization::align << this->interval_.first << this->interval_.second
                   << this->road_category_ << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> holo::serialization::align >> this->interval_.first >> this->interval_.second >>
            this->road_category_ >> holo::serialization::align;
    }

private:
    IntervalType interval_;  ///< First element is distance from start point of interval to car position, second is end
                             ///< point to car position.
    holo::common::RoadCategory road_category_;  ///< Road category of this interval.
};                                              // RoadTypeInterval

/**
 * @brief A sequence presents attributes on a road.
 * @details Attributes of sequence base on a ref point.
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnxymWmsPSdPBdcnEQfe362b
 *
 * @tparam T Road attribute type.
 * @tparam size .
 */
template <typename T, std::size_t MAX_SIZE = 1024U>
class RoadRefPointAttributes : public holo::container::details::VectorBase<T, MAX_SIZE>
{
public:
    using PointType = holo::geometry::Point3T<holo::float64_t>;

    using Base = holo::container::details::VectorBase<T, MAX_SIZE>;
    using Base::VectorBase;

    static size_t const SIZE_VALUE = MAX_SIZE;

    using value_type             = typename Base::value_type;
    using allocator_type         = typename Base::allocator_type;
    using size_type              = typename Base::size_type;
    using difference_type        = typename Base::difference_type;
    using reference              = typename Base::reference;
    using const_reference        = typename Base::const_reference;
    using pointer                = typename Base::pointer;
    using const_pointer          = typename Base::const_pointer;
    using iterator               = typename Base::iterator;
    using const_iterator         = typename Base::const_iterator;
    using reverse_iterator       = typename Base::reverse_iterator;
    using const_reverse_iterator = typename Base::const_reverse_iterator;
    using Timestamp              = holo::common::Timestamp;

    /**
     * @brief Default constructor
     */
    RoadRefPointAttributes() noexcept : Base(), timestamp_(), ref_point_(), coordinate_()
    {
    }

    /**
     * @brief Get timestamp.
     *
     * @return A const reference of Timestamp object.
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Get timestamp.
     *
     * @return A const reference of Timestamp object.
     */
    Timestamp& GetTimestamp() noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Set timestamp.
     *
     * @param[in] timestamp A timestamp object.
     * @return Nothing.
     */
    void SetTimestamp(Timestamp const& timestamp)
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get ref point.
     *
     * @return A const reference of PointType object.
     */
    PointType const& GetRefPoint() const noexcept
    {
        return this->ref_point_;
    }

    /**
     * @brief Get ref point.
     *
     * @return A const reference of PointType object.
     */
    PointType& GetRefPoint() noexcept
    {
        return this->ref_point_;
    }

    /**
     * @brief Set current point.
     *
     * @param[in] point A point
     * @return Nothing.
     */
    void SetRefPoint(PointType const& point) noexcept
    {
        this->ref_point_ = point;
    }

    /**
     * @brief Get coordinate.
     *
     * @return A Coordinate object.
     */
    holo::common::Coordinate GetCoordinate() const noexcept
    {
        return this->coordinate_;
    }

    /**
     * @brief Set coordinate.
     *
     * @param[in] coordinate A const Coordinate object.
     * @return Nothing.
     */
    void SetCoordinate(holo::common::Coordinate const coordinate) noexcept
    {
        this->coordinate_ = coordinate;
    }

    template <size_t ALIGN = 4U>
    std::size_t GetSerializedSize() const noexcept
    {
        std::size_t size = timestamp_.GetSerializedSize<ALIGN>() + ref_point_.GetSerializedSize<ALIGN>() +
                           holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_),
                                                                      static_cast<uint32_t>(this->size()));
        for (auto const& value : (*this))
        {
            size += value.template GetSerializedSize<ALIGN>();
        }
        return size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << ref_point_ << coordinate_ << static_cast<uint32_t>(this->size())
                   << holo::serialization::align;

        for (auto const& value : (*this))
        {
            serializer << value;
        }

        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t size = 0U;
        deserializer >> this->timestamp_ >> this->ref_point_ >> this->coordinate_ >> size >> holo::serialization::align;

        this->resize(size);

        for (size_t idx = 0U; idx < size; ++idx)
        {
            deserializer >> (*this)[idx];
        }
        deserializer >> holo::serialization::align;
    }

private:
    Timestamp                timestamp_;   ///< Timestamp of message.
    PointType                ref_point_;   ///< Ref point.
    holo::common::Coordinate coordinate_;  ///< Coordinate of ref point.
};                                         // RoadRefPointAttributes

/**
 * @}
 *
 */

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_ROAD_REF_POINT_ATTRIBUTES_H_ */
