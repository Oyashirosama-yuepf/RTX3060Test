/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_distance.h
 * @brief This header file defines distance between obstacles and the vehicle 
 *        border of both sides.
 * @author chengxiang(chengxiang@holomaitc.com)
 * @date 2021-07-30
 */

#ifndef HOLO_PARKING_BASE_SURROUNDING_OBSTACLE_IDISTANCE_H_
#define HOLO_PARKING_BASE_SURROUNDING_OBSTACLE_IDISTANCE_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace surroundings
{

/**
 * @brief This class defines distance from the vehicle border to the obstacles 
 *        of both sides seperately.
 */
class ObstacleDistance
{
public:
    ObstacleDistance() noexcept
        :timestamp_()
        ,is_left_obs_exists_(false)
        ,dist_to_left_obs_(0.0)
        ,is_right_obs_exists_(false)
        ,dist_to_right_obs_(0.0)
    {}

    /* timestamp_ */
    holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(holo::common::Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /* is_left_obs_exists_ */
    bool_t LeftObstacleExists() const noexcept
    {
        return is_left_obs_exists_;
    }

    void SetLeftObstacleExists( bool_t is_left_obs_exists )
    {
        is_left_obs_exists_ = is_left_obs_exists;
    }

    float32_t GetDistance2LeftObstacle() const noexcept
    {
        return dist_to_left_obs_;
    }

    void SetDistance2LeftObstacle( float32_t dist )
    {
        dist_to_left_obs_ = dist;
    }

    /* is_left_obs_exists_ */
    bool_t RightObstacleExists() const noexcept
    {
        return is_right_obs_exists_;
    }

    void SetRightObstacleExists( bool_t is_right_obs_exists )
    {
        is_right_obs_exists_ = is_right_obs_exists;
    }

    float32_t GetDistance2RightObstacle() const noexcept
    {
        return dist_to_right_obs_;
    }

    void SetDistance2RightObstacle( float32_t dist )
    {
        dist_to_right_obs_ = dist;
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
        return timestamp_.GetSerializedSize<ALIGN>() +
                holo::serialization::SerializedSize<ALIGN>(
                   is_left_obs_exists_
                 , dist_to_left_obs_
                 , is_right_obs_exists_
                 , dist_to_right_obs_
                );
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
        /* serialize data */
        serializer << timestamp_         << is_left_obs_exists_ 
                   << dist_to_left_obs_  << is_right_obs_exists_ 
                   << dist_to_right_obs_ << holo::serialization::align;
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
        /* deserialize data */
        deserializer >> timestamp_         >> is_left_obs_exists_ 
                     >> dist_to_left_obs_  >> is_right_obs_exists_ 
                     >> dist_to_right_obs_ >> holo::serialization::align;
    }

private:
    holo::common::Timestamp timestamp_;           ///< timestamp

    bool_t                  is_left_obs_exists_;
    float32_t               dist_to_left_obs_;
    bool_t                  is_right_obs_exists_;
    float32_t               dist_to_right_obs_;
};


}  // namespace surroundings
}  // namespace parking
}  // namespace holo

#endif
