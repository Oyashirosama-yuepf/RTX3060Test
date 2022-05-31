/**
 * @file path.h
 * @brief This is used to define the path
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-10-21
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_COMMON_DETAILS_PATH_H_
#define HOLO_COMMON_DETAILS_PATH_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/container/details/vector.h>
#include <holo/geometry/point3.h>
#include <holo/log/hololog.h>
#include <holo/serialization/serialization.h>

#include <vector>

namespace holo
{
namespace common
{
namespace details
{
/**
 * @brief this class describes point on path
 */
template <typename T>
class PathPointT : public holo::geometry::Point3T<T>
{
public:
    using ScalarType = T;
    using Base       = holo::geometry::Point3T<T>;
    using Point3Type = Base;

    static size_t const SIZE_VALUE = Base::SIZE_VALUE;

    /**
     * @brief default constructor
     */
    PathPointT() noexcept
      : Point3Type()
      , theta_(0.0)
      , curvature_(0.0)
      , speed_(0.0)
      , acceleration_(0.0)
      , distance_(0.0)
      , time_(0.0)
    {
    }

    PathPointT(ScalarType x, ScalarType y, ScalarType z) noexcept
      : Point3Type(x, y, z)
      , theta_(0.0)
      , curvature_(0.0)
      , speed_(0.0)
      , acceleration_(0.0)
      , distance_(0.0)
      , time_(0.0)
    {
    }

    /* theta_ */
    ScalarType GetTheta() const noexcept
    {
        return theta_;
    }

    void SetTheta(ScalarType theta)
    {
        theta_ = theta;
    }

    /* curvature_ */
    ScalarType GetCurvature() const noexcept
    {
        return curvature_;
    }

    void SetCurvature(ScalarType curvature)
    {
        curvature_ = curvature;
    }

    /* speed_ */
    ScalarType GetSpeed() const noexcept
    {
        return speed_;
    }

    void SetSpeed(ScalarType speed) noexcept
    {
        speed_ = speed;
    }

    /* acceleration_ */
    ScalarType GetAcceleration() const noexcept
    {
        return acceleration_;
    }

    void SetAcceleration(ScalarType acceleration) noexcept
    {
        acceleration_ = acceleration;
    }

    /* distance */
    ScalarType GetDistance() const noexcept
    {
        return distance_;
    }

    void SetDistance(ScalarType const distance) noexcept
    {
        distance_ = distance;
    }

    /* time */
    ScalarType GetTime() const noexcept
    {
        return time_;
    }

    void SetTime(ScalarType const time) noexcept
    {
        time_ = time;
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
               holo::serialization::SerializedSize<ALIGN>(theta_, curvature_, speed_, acceleration_, distance_, time_);
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
        Base::Serialize(serializer);
        serializer << theta_ << curvature_ << speed_ << acceleration_ << distance_ << time_
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
        Base::Deserialize(deserializer);
        deserializer >> theta_ >> curvature_ >> speed_ >> acceleration_ >> distance_ >> time_ >>
            holo::serialization::align;
    }

private:
    ScalarType theta_;  ///< the heading angle of the point [rad]

    ScalarType curvature_;  ///< the curvature of the path on this point

    ScalarType speed_;  ///< the tag speed of this point [m/s]

    ScalarType acceleration_;  ///< the tag acceleration of this point [m/s2]

    ScalarType distance_;  ///< the distance difference to ideal point along the path [m]

    ScalarType time_;  ///< the time difference to ideal point point [s]
};

/**
 * @brief A pathpoint sequence presents a path.
 *
 * @tparam T Pathpoint scalar type.
 * @tparam size .
 */
template <typename T, size_t SIZE = 256U>
class PathT : public holo::container::details::VectorBase<PathPointT<T>, SIZE>
{
public:
    using ScalarType = T;
    using Point3Type = holo::geometry::Point3T<ScalarType>;
    using PointType  = PathPointT<ScalarType>;

    using Base       = holo::container::details::VectorBase<PathPointT<T>, SIZE>;
    using Coordinate = holo::common::Coordinate;

    using Base::VectorBase;

    static size_t const SIZE_VALUE = SIZE;

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

    enum class ValidValue : uint32_t
    {
        POSITION     = 0x01,
        THETA        = 0x02,
        CURVATURE    = 0x04,
        SPEED        = 0x08,
        ACCELERATION = 0x10,
        DISTANCE     = 0x20,
        TIME         = 0x40,
    };

    enum class PlanningState : uint32_t
    {
        UNKNOWN  = 0U,
        FORWARD  = 1U,
        BACKWARD = 2U,
        HOLD     = 3U,
        PARK     = 4U,
    };

    /**
     * @brief default constructor
     */
    PathT() noexcept
      : Base()
      , timestamp_()
      , coordinate_(Coordinate::Utm6Coordinate(50U, false))
      , valid_value_(0)
      , planning_state_(PlanningState::UNKNOWN)
    {
    }

    Timestamp& GetTimestamp() noexcept
    {
        return timestamp_;
    }

    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    void SetTimestamp(const Timestamp& value) noexcept
    {
        timestamp_ = value;
    }

    void SetCoordinate(Coordinate value) noexcept
    {
        coordinate_ = value;
    }

    PlanningState GetPlanningState() const noexcept
    {
        return planning_state_;
    }

    void SetPlanningState(PlanningState const planning_state) noexcept
    {
        planning_state_ = planning_state;
    }

    uint32_t GetValidValue() const noexcept
    {
        return valid_value_;
    }

    void SetValidValue(uint32_t value) noexcept
    {
        valid_value_ = value;
    }

    void SetSingleValidValue(ValidValue value)
    {
        valid_value_ |= static_cast<uint32_t>(value);
    }

    bool_t IsPositionValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::POSITION);
    }

    bool_t IsThetaValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::THETA);
    }

    bool_t IsCurvatureValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::CURVATURE);
    }

    bool_t IsSpeedValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::SPEED);
    }

    bool_t IsAccelerationValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::ACCELERATION);
    }

    bool_t IsDistanceValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::DISTANCE);
    }

    bool_t IsTimeValid() const noexcept
    {
        return valid_value_ & static_cast<uint32_t>(ValidValue::TIME);
    }

    bool_t AreAllDataValid() const noexcept
    {
        return IsPositionValid() && IsThetaValid() && IsCurvatureValid() && IsSpeedValid() && IsAccelerationValid() &&
               IsDistanceValid() && IsTimeValid();
    }

    /**
     * @brief this function is used find the closest point on the path
     *
     * @param start The process of finding will start at this iterator.
     * @param target_point The target point needs to find the closest point.
     *
     * @return the closest point's iterator. if something is wrong during finding, return end iterator
     */
    const_iterator FindClosestPoint(const_iterator start, const Point3Type& target_point) const
    {
        if (this->empty())
        {
            LOG(ERROR) << "The path point list is empty, could not find the cloest point";
            return this->end();
        }

        if (start == this->end())
        {
            LOG(ERROR) << "The start iterator is invalid";
            return this->end();
        }

        PathT<T, SIZE>::const_iterator iter               = start;
        float64_t                      closest_dis_sqr    = target_point.DistSqr((*iter));
        float64_t                      dis_sqr            = 0.0;
        bool                           find_closest_point = false;
        for (; iter != this->end(); iter++)
        {
            dis_sqr = target_point.DistSqr((*iter));
            if (dis_sqr <= closest_dis_sqr)
            {
                closest_dis_sqr = dis_sqr;
            }
            else
            {
                find_closest_point = true;
                break;
            }
        }

        if (!find_closest_point)
        {
            LOG(INFO) << "Scaning the whole path, the distance to the target point is getting smaller and smaller";
            LOG(INFO) << "so return the last point as the closest point";
            iter--;
        }
        /* the cloest idx should be idx-1, but we only care the point ahead of us
           for accurate calculatation, we should find if the closet point is also in ahead
           however, we are going to move ahead,
           so the point ahead of the the close point would be the point we choose as the closest one */
        return iter;
    }

    /**
     * @brief this function is used find the closest point on the path from the beginning of the path
     *
     * @param target_point The target point needs to find the closest point.
     *
     * @return the closest point's iterator. if something is wrong during finding, return end iterator
     */
    const_iterator FindClosestPoint(const Point3Type& target_point) const
    {
        return FindClosestPoint(this->begin(), target_point);
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
                              holo::serialization::SerializedSize<ALIGN>(
                                  static_cast<uint32_t>(coordinate_), valid_value_,
                                  static_cast<uint32_t>(planning_state_), static_cast<uint32_t>(this->size()));
        for (auto const& pt : (*this))
        {
            aligned_size += pt.template GetSerializedSize<ALIGN>();
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
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << static_cast<uint32_t>(coordinate_) << valid_value_
                   << static_cast<uint32_t>(planning_state_) << static_cast<uint32_t>(this->size());
        for (auto const& pt : (*this))
        {
            serializer << pt;
        }
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
        uint32_t coord;
        uint32_t size;
        uint32_t planning_state;
        deserializer >> timestamp_ >> coord >> valid_value_ >> planning_state >> size;
        coordinate_ = coord;
        this->resize(size);
        for (auto& pt : (*this))
        {
            deserializer >> pt;
        }
        planning_state_ = static_cast<PlanningState>(planning_state);
    }

private:
    Timestamp     timestamp_{};
    Coordinate    coordinate_{};
    uint32_t      valid_value_{};
    PlanningState planning_state_{};  ///< planning case forward backward hold park
};

}  // namespace details
}  // namespace common
}  // namespace holo

#endif
