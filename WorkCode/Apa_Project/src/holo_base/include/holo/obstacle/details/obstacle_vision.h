/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_vision.h
 * @brief This header file defines ObstacleVisionT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_VISION_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_VISION_H_

#include <limits>
#include <memory>
#include <vector>

#include <holo/common/classification.h>
#include <holo/common/sensor_id.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/serialization/serialization.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/keypoint3.h>

namespace holo
{
namespace obstacle
{
namespace details
{
/**
 * @brief Obstacle from vision sensor
 *
 * @tparam T obstacle type, only support float32_t and float64_t
 */
template <typename T, size_t SIZE = 8U>
class ObstacleVisionT : public ObstacleBaseT<T>
{
public:
    static const uint32_t SIZE_VALUE = SIZE;

    using ScalarType         = T;
    using Point3Type         = holo::geometry::Point3T<ScalarType>;
    using Vector3Type        = holo::numerics::Vector3T<ScalarType>;
    using KeyPoint2Type      = holo::vision::KeyPoint2T<ScalarType>;
    using KeyPoint3Type      = holo::vision::KeyPoint3T<ScalarType>;
    using Base               = ObstacleBaseT<T>;
    using SensorIdType       = typename Base::SensorId;
    using ClassificationType = typename Base::Classification;

    /**
     * @brief Default constructor
     */
    ObstacleVisionT() noexcept
      : Base{}
      , relative_velocity_{Vector3Type::Zero()}
      , acceleration_{Vector3Type::Zero()}
      , position_sigma_{Point3Type::Zero()}
      , relative_velocity_sigma_{Vector3Type::Zero()}
      , acceleration_sigma_{Vector3Type::Zero()}
      , image_bounding_box2d_{}
      , bounding_box3d_{}
      , motion_status_{MotionStatus::UNKNOWN}
      , cut_in_cut_out_{CutInCutOut::UNKNOWN}
      , key_points_2d_{}
      , key_points_3d_{}
    {
    }

    /**
     * @brief Constructor
     *
     * @param timestamp Obstacle time stamp
     * @param coord Obstacle coordinate
     * @param obstacle_id Obstacle id
     * @param sensor_id Obstacle sensor id
     * @param classification Obstacle classification
     * @param obstacle_exist_score Obstacle existence confidence
     * @param position Obstacle position
     * @param relative_velocity Obstacle relative velocity
     * @param acceleration Obstacle acceleration
     * @param position_sigma Obstacle poistion standard deviation
     * @param relative_velocity_sigma Obstacle relative velocity standard deviation
     * @param acceleration_sigma Obstacle acceleration standard deviation
     * @param motion_status Obstacle motion state
     * @param image_bounding_box Obstacle 2D bbox in image panel
     * @param bounding_box3d Obstacle 3D bbox in real world
     * @param cut_in_cut_out Obstacle prediction state
     * @param key_points_2d Obstacle key points 2d
     * @param key_points_3d Obstacle key points 3d
     */
    ObstacleVisionT(holo::common::Timestamp const& timestamp, holo::common::Coordinate const coord,
                    uint32_t const obstacle_id, SensorIdType const& sensor_id, ClassificationType const& classification,
                    float32_t const obstacle_exist_score, Point3Type const& position,
                    Vector3Type const& relative_velocity, Vector3Type const& acceleration,
                    Point3Type const& position_sigma, Vector3Type const& relative_velocity_sigma,
                    Vector3Type const& acceleration_sigma, MotionStatus const motion_status,
                    holo::geometry::Box2f const& image_bounding_box2d, holo::geometry::Box3f const& bounding_box3d,
                    CutInCutOut const                                         cut_in_cut_out,
                    holo::container::Vector<KeyPoint2Type, SIZE_VALUE> const& key_points_2d,
                    holo::container::Vector<KeyPoint3Type, SIZE_VALUE> const& key_points_3d) noexcept
      : Base(timestamp, coord, obstacle_id, sensor_id, classification, obstacle_exist_score, position)
      , relative_velocity_(relative_velocity)
      , acceleration_(acceleration)
      , position_sigma_(position_sigma)
      , relative_velocity_sigma_(relative_velocity_sigma)
      , acceleration_sigma_(acceleration_sigma)
      , image_bounding_box2d_(image_bounding_box2d)
      , bounding_box3d_(bounding_box3d)
      , motion_status_(motion_status)
      , cut_in_cut_out_(cut_in_cut_out)
      , key_points_2d_(key_points_2d)
      , key_points_3d_(key_points_3d)
    {
    }

    /**
     * @brief Get obstacle relative velocity
     *
     * @return obstacle relative velocity
     */
    Vector3Type const& GetRelativeVelocity() const noexcept
    {
        return relative_velocity_;
    }

    /**
     * @brief Set obstacle relative velocity
     *
     * @param relative_velocity obstacle relative velocity
     */
    void SetRelativeVelocity(Vector3Type const& relative_velocity) noexcept
    {
        this->relative_velocity_ = relative_velocity;
    }

    /**
     * @brief Get obstacle acceleration
     *
     * @return obstacle acceleration
     */
    Vector3Type const& GetAcceleration() const noexcept
    {
        return acceleration_;
    }

    /**
     * @brief Set obstacle acceleration
     *
     * @param acceleration obstacle acceleration
     */
    void SetAcceleration(Vector3Type const& acceleration) noexcept
    {
        this->acceleration_ = acceleration;
    }

    /**
     * @brief Get osbtacle position standard deviation
     *
     * @return osbtacle position standard deviation
     */
    Point3Type const& GetPositionSigma() const noexcept
    {
        return position_sigma_;
    }

    /**
     * @brief Set obstacle position standard deviation
     *
     * @param position_sigma obstacle position standard deviation
     */
    void SetPositionSigma(Point3Type const& position_sigma) noexcept
    {
        this->position_sigma_ = position_sigma;
    }

    /**
     * @brief Get obstacle relative velocity standard deviation
     *
     * @return obstacle relative velocity standard deviation
     */
    Vector3Type const& GetRelativeVelocitySigma() const noexcept
    {
        return relative_velocity_sigma_;
    }

    /**
     * @brief Set obstacle velocity standard deviation
     *
     * @param relative_velocity_sigma obstacle velocity standard deviation
     */
    void SetRelativeVelocitySigma(Vector3Type const& relative_velocity_sigma) noexcept
    {
        this->relative_velocity_sigma_ = relative_velocity_sigma;
    }

    /**
     * @brief Get obstacle acceleration standard deviation
     *
     * @return obstacle acceleration standard deviation
     */
    Vector3Type const& GetAccelerationSigma() const noexcept
    {
        return acceleration_sigma_;
    }

    /**
     * @brief Set obstacle acceleration standard deviation
     *
     * @param acceleration_sigma obstacle acceleration standard deviation
     */
    void SetAccelerationSigma(Vector3Type const& acceleration_sigma) noexcept
    {
        this->acceleration_sigma_ = acceleration_sigma;
    }

    /**
     * @brief Get obstacle motion status
     *
     * @return obstacle motion status
     */
    MotionStatus GetMotionStatus() const noexcept
    {
        return motion_status_;
    }

    /**
     * @brief Get obstacle motion status
     *
     * @param motion_status obstacle motion status
     */
    void SetMotionStatus(MotionStatus const motion_status) noexcept
    {
        this->motion_status_ = motion_status;
    }

    /**
     * @brief Get obstacle bounding box in 2D image panel
     *
     * @return obstacle bbox 2d
     */
    holo::geometry::Box2f const& GetImageBBox2D() const noexcept
    {
        return image_bounding_box2d_;
    }

    /**
     * @brief Set obstacle bounding box in 2D image panel
     *
     * @param image_bounding_box2d bounding box in 2D image panel
     */
    void SetImageBBox2D(holo::geometry::Box2f const& image_bounding_box2d) noexcept
    {
        this->image_bounding_box2d_ = image_bounding_box2d;
    }

    /**
     * @brief Get obstacle bounding box in 3D world
     *
     * @return obstacle bbox 3d
     */
    holo::geometry::Box3f const& GetObstacleBBox3D() const noexcept
    {
        return bounding_box3d_;
    }

    /**
     * @brief Set obstacle bounding box in 3D world
     *
     * @param bounding_box3d bounding box in 3D world
     */
    void SetObstacleBBox3D(holo::geometry::Box3f const& bounding_box3d) noexcept
    {
        this->bounding_box3d_ = bounding_box3d;
    }

    /**
     * @brief Get obstacle prediction information
     *
     * @return cut in cut out information
     */
    CutInCutOut const& GetCutInCutOut() const noexcept
    {
        return cut_in_cut_out_;
    }

    /**
     * @brief Set obstacle prediction information
     *
     * @param cut_in_cut_out obstacle cut in cut out information
     */
    void SetCutInCutOut(CutInCutOut const& cut_in_cut_out) noexcept
    {
        this->cut_in_cut_out_ = cut_in_cut_out;
    }

    /**
     * @brief Get key points size
     * @deprecated replaced by GetKeyPoints2DSize()
     * 
     * @return key points size
     */
    [[deprecated]] uint32_t GetKeyPointsSize() const noexcept
    {
        return key_points_2d_.size();
    }

    /**
     * @brief Get key points of obstacle
     * @deprecated replaced by GetKeyPoints2D()
     *
     * @return key points of obstacle
     */
    [[deprecated]] std::vector<KeyPoint2Type> const GetKeyPoints() const noexcept
    {
        std::vector<KeyPoint2Type> key_points;
        for(auto const& value: key_points_2d_)
        {
            key_points.push_back(value);
        }
        return key_points;
    }

    /**
     * @brief Set key points for obstacle
     * @deprecated replaced by SetKeyPoints2D()
     * 
     * @param key_points key points of obstacle
     */
    [[deprecated]] void SetKeyPoints(std::vector<KeyPoint2Type> const& key_points)
    {
        if(key_points.size() > SIZE_VALUE)
        {
            throw holo::exception::BadAllocException();
        }

        key_points_2d_.clear();
        for(auto const& value: key_points)
        {
            key_points_2d_.push_back(value);
        }
    }

    /**
     * @brief Get key points 2D size
     *
     * @return key point2s size
     */
    uint32_t GetKeyPoints2DSize() const noexcept
    {
        return key_points_2d_.size();
    }

    /**
     * @brief Get key points 2D of obstacle
     *
     * @return key points 2D of obstacle
     */
    holo::container::Vector<KeyPoint2Type, SIZE_VALUE> const& GetKeyPoints2D() const noexcept
    {
        return key_points_2d_;
    }

    /**
     * @brief Set key points 2D for obstacle
     *
     * @param key_points_2d key points 2D of obstacle
     */
    void SetKeyPoints2D(holo::container::Vector<KeyPoint2Type, SIZE_VALUE> const& key_points_2d) noexcept
    {
        key_points_2d_ = key_points_2d;
    }

    /**
     * @brief Set key points 2D for obstacle with rvalue
     *
     * @param key_points_2d key points 2D of obstacle
     */
    void SetKeyPoints2D(holo::container::Vector<KeyPoint2Type, SIZE_VALUE>&& key_points_2d)
    {
        key_points_2d_ = std::move(key_points_2d);
    }

    /**
     * @brief Get key points 3D size
     *
     * @return key points 3D size
     */
    uint32_t GetKeyPoints3DSize() const noexcept
    {
        return key_points_3d_.size();
    }

    /**
     * @brief Get key points 3D of obstacle
     *
     * @return key points 3D of obstacle
     */
    holo::container::Vector<KeyPoint3Type, SIZE_VALUE> const& GetKeyPoints3D() const noexcept
    {
        return key_points_3d_;
    }

    /**
     * @brief Set key points 3D for obstacle
     *
     * @param key_points_3d key point3s of obstacle
     */
    void SetKeyPoints3D(holo::container::Vector<KeyPoint3Type, SIZE_VALUE> const& key_points_3d) noexcept
    {
        key_points_3d_ = key_points_3d;
    }

    /**
     * @brief Set key points 3D for obstacle with rvalue
     *
     * @param key_points_3d key points 3D of obstacle
     */
    void SetKeyPoints3D(holo::container::Vector<KeyPoint3Type, SIZE_VALUE>&& key_points_3d)
    {
        key_points_3d_ = std::move(key_points_3d);
    }

    /**
     * @brief Serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept override
    {
        std::stringstream ss;
        ss << "ObstacleVisionT: (" << Base::ToString() << ", relative_velocity_: " << this->relative_velocity_
           << ", acceleration_: " << this->acceleration_ << ", position_sigma_: " << this->position_sigma_
           << ", relative_velocity_sigma_: " << this->relative_velocity_sigma_
           << ", acceleration_sigma_: " << this->acceleration_sigma_
           << ", motion_status_: " << static_cast<uint32_t>(this->motion_status_)
           << ", image_bounding_box2d_: " << this->image_bounding_box2d_.ToString()
           << ", bounding_box3d_: " << this->bounding_box3d_.ToString()
           << ", cut_in_cut_out_: " << static_cast<uint32_t>(this->cut_in_cut_out_) << ", key_points_2d_: ";
        for (uint32_t i = 0; i < this->key_points_2d_.size(); ++i)
        {
            ss << this->key_points_2d_[i] << " ";
        }
        ss << ", key_points_3d_: ";
        for (uint32_t i = 0; i < this->key_points_3d_.size(); ++i)
        {
            ss << this->key_points_3d_[i] << " ";
        }
        ss << ")" << std::endl;

        return ss.str();
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
        size_t aligned_size =
            Base::template GetSerializedSize<ALIGN>() + relative_velocity_.template GetSerializedSize<ALIGN>() +
            acceleration_.template GetSerializedSize<ALIGN>() + position_sigma_.template GetSerializedSize<ALIGN>() +
            relative_velocity_sigma_.template GetSerializedSize<ALIGN>() +
            acceleration_sigma_.template GetSerializedSize<ALIGN>() + image_bounding_box2d_.GetSerializedSize<ALIGN>() +
            bounding_box3d_.GetSerializedSize<ALIGN>() +
            holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(motion_status_),
                                                       static_cast<uint8_t>(cut_in_cut_out_)) +
            key_points_2d_.template GetSerializedSize<ALIGN>() + key_points_3d_.template GetSerializedSize<ALIGN>();

        return aligned_size;
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
        Base::Serialize(serializer);
        serializer << relative_velocity_ << acceleration_ << position_sigma_ << relative_velocity_sigma_
                   << acceleration_sigma_ << image_bounding_box2d_ << bounding_box3d_
                   << static_cast<uint8_t>(motion_status_) << static_cast<uint8_t>(cut_in_cut_out_) << key_points_2d_
                   << key_points_3d_;
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
        uint8_t cur_motion_status = 0U, cur_cut_in_cut_out = 0U;
        Base::Deserialize(deserializer);
        deserializer >> relative_velocity_ >> acceleration_ >> position_sigma_ >> relative_velocity_sigma_ >>
            acceleration_sigma_ >> image_bounding_box2d_ >> bounding_box3d_ >> cur_motion_status >>
            cur_cut_in_cut_out >> key_points_2d_ >> key_points_3d_;

        motion_status_  = static_cast<MotionStatus>(cur_motion_status);
        cut_in_cut_out_ = static_cast<CutInCutOut>(cur_cut_in_cut_out);
    }

private:
    Vector3Type                                        relative_velocity_;
    Vector3Type                                        acceleration_;
    Point3Type                                         position_sigma_;
    Vector3Type                                        relative_velocity_sigma_;
    Vector3Type                                        acceleration_sigma_;
    holo::geometry::Box2f                              image_bounding_box2d_;
    holo::geometry::Box3f                              bounding_box3d_;
    MotionStatus                                       motion_status_;
    CutInCutOut                                        cut_in_cut_out_;
    holo::container::Vector<KeyPoint2Type, SIZE_VALUE> key_points_2d_;  ///< diffierent classified obstacle has
                                                                        ///< different key point2s defination
    holo::container::Vector<KeyPoint3Type, SIZE_VALUE> key_points_3d_;  ///< diffierent classified obstacle has
                                                                        ///< different key point3s defination
};

}  // namespace details
}  // namespace obstacle
}  // namespace holo

#endif
