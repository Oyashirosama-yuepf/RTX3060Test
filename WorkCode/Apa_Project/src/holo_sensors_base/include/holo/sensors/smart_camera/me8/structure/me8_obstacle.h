/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_obstacle.h
 * @brief A class to describe me8 obstacle
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/14
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_ME8_OBSTACLE_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_ME8_OBSTACLE_H_

#include <holo/common/coordinate.h>
#include <holo/common/details/classification.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/core/common.h>
#include <holo/core/types.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_vision.h>

namespace holo
{
namespace sensors
{
namespace me8
{
using holo::common::Classification;
enum class Assignment : uint8_t
{
    NEXT_LEFT_LANE = 0,
    LEFT_LANE,
    EGO_LANE,
    RIGHT_LANE,
    NEXT_RIGHT_LANE,
    NOT_ASSIGNED,
    ASSIGNMENT_LENGTH
};
enum class MotionCategory : uint8_t
{
    MC_UNDEFINED = 0,
    MC_PASSING,
    MC_PASSING_IN,
    MC_PASSING_OUT,
    MC_CLOSE_CUT_IN,
    MC_MOVING_IN,
    MC_MOVING_OUT,
    MC_CROSSING,
    MC_LTAP,
    MC_RTAP,
    MC_MOVING,
    MC_PRECEEDING,
    MC_ONCOMING,
    MOTION_CATEGORY_LENGTH
};

class Me8ObsHeader
{
public:
    Me8ObsHeader() : sync_frame_index_(0), num_of_video_objs_(0), vd_cipv_id_(0), vd_cipv_lost_(0), obj_vd_allow_acc_(0)
    {
    }

    inline void SetSyncFrameIndex(uint8_t sync_frame_index) noexcept
    {
        sync_frame_index_ = sync_frame_index;
    }

    inline uint8_t GetSyncFrameIndex() const noexcept
    {
        return sync_frame_index_;
    }

    inline void SetNumOfVideoObjs(uint8_t num_of_video_objs) noexcept
    {
        num_of_video_objs_ = num_of_video_objs;
    }

    inline uint8_t GetNumOfVideoObjs() const noexcept
    {
        return num_of_video_objs_;
    }

    inline void SetVdCipvId(uint8_t vd_cipv_id) noexcept
    {
        vd_cipv_id_ = vd_cipv_id;
    }

    inline uint8_t GetVdCipvId() const noexcept
    {
        return vd_cipv_id_;
    }

    inline void SetVdCipvLost(uint8_t vd_cipv_lost) noexcept
    {
        vd_cipv_lost_ = vd_cipv_lost;
    }

    inline uint8_t GetVdCipvLost() const noexcept
    {
        return vd_cipv_lost_;
    }

    inline void SetObjVdAllowAcc(uint8_t obj_vd_allow_acc) noexcept
    {
        obj_vd_allow_acc_ = obj_vd_allow_acc;
    }

    inline uint8_t GetObjVdAllowAcc() const noexcept
    {
        return obj_vd_allow_acc_;
    }

private:
    uint8_t sync_frame_index_;   //! 0|8@1+ (1,0) [0|255] "counter" Vector__XXX
    uint8_t num_of_video_objs_;  //! 8|4@1+ (1,0) [0|12] "counter" Vector__XXX
    uint8_t vd_cipv_id_;         //! 12|7@1+ (1,0) [0|127] "counter" Vector__XXX
    uint8_t vd_cipv_lost_;       //! 19|2@1+ (1,0) [0|2] "ENUM" Vector__XXX
    uint8_t obj_vd_allow_acc_;   //! 21|2@1+ (1,0) [0|2] "ENUM" Vector__XXX
};

class Me8Obstacle
{
public:
    Me8Obstacle()
      : timestamp_()
      , object_id_(0)
      , object_class_(0)
      , object_width_(0.0f)
      , object_length_(0.0f)
      , relative_long_velocity_(0.0f)
      , lane_assignment_(0)
      , relative_lat_velocity_(0.0f)
      , absolute_long_acc_(0.0f)
      , long_distance_acc_(0.0f)
      , lateral_distance_(0.0f)
      , absolute_speed_(0.0f)
      , object_motion_status_(0)
      , object_motion_category_(0)
      , brake_light_(false)
      , turn_indicator_right_(false)
      , turn_indicator_left_(false)
      , light_indicator_validity_(false)
      , object_angle_mid_(0.0f)
      , object_angle_rate_(0.0f)
      , part_a_valid_(false)
      , part_b_valid_(false)
      , part_c_valid_(false)
    {
    }

    Me8Obstacle(const Me8Obstacle& other) noexcept
      : timestamp_(other.timestamp_)
      , object_id_(other.object_id_)
      , object_class_(other.object_class_)
      , object_width_(other.object_width_)
      , object_length_(other.object_length_)
      , relative_long_velocity_(other.relative_long_velocity_)
      , lane_assignment_(other.lane_assignment_)
      , relative_lat_velocity_(other.relative_lat_velocity_)
      , absolute_long_acc_(other.absolute_long_acc_)
      , long_distance_acc_(other.long_distance_acc_)
      , lateral_distance_(other.lateral_distance_)
      , absolute_speed_(other.absolute_speed_)
      , object_motion_status_(other.object_motion_status_)
      , object_motion_category_(other.object_motion_category_)
      , brake_light_(other.brake_light_)
      , turn_indicator_right_(other.turn_indicator_right_)
      , turn_indicator_left_(other.turn_indicator_left_)
      , light_indicator_validity_(other.light_indicator_validity_)
      , object_angle_mid_(other.object_angle_mid_)
      , object_angle_rate_(other.object_angle_rate_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
      , part_c_valid_(other.part_c_valid_)
    {
    }

    Me8Obstacle& operator=(const Me8Obstacle& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_                = other.timestamp_;
        object_id_                = other.object_id_;
        object_class_             = other.object_class_;
        object_width_             = other.object_width_;
        object_length_            = other.object_length_;
        relative_long_velocity_   = other.relative_long_velocity_;
        lane_assignment_          = other.lane_assignment_;
        relative_lat_velocity_    = other.relative_lat_velocity_;
        absolute_long_acc_        = other.absolute_long_acc_;
        long_distance_acc_        = other.long_distance_acc_;
        lateral_distance_         = other.lateral_distance_;
        absolute_speed_           = other.absolute_speed_;
        object_motion_status_     = other.object_motion_status_;
        object_motion_category_   = other.object_motion_category_;
        brake_light_              = other.brake_light_;
        turn_indicator_right_     = other.turn_indicator_right_;
        turn_indicator_left_      = other.turn_indicator_left_;
        light_indicator_validity_ = other.light_indicator_validity_;
        object_angle_mid_         = other.object_angle_mid_;
        object_angle_rate_        = other.object_angle_rate_;
        part_a_valid_             = other.part_a_valid_;
        part_b_valid_             = other.part_b_valid_;
        part_c_valid_             = other.part_c_valid_;
        return *this;
    }
    void ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const;
    void ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
                                            const holo::common::Extrinsicf&             extrinsic) const;

    inline void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    inline holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    inline void SetObjectId(uint8_t id) noexcept
    {
        object_id_ = id;
    }

    inline uint8_t GetObjectId() const noexcept
    {
        return object_id_;
    }

    inline void SetObjectClass(uint8_t object_class) noexcept
    {
        object_class_ = object_class;
    }

    inline uint8_t GetObjectClass() const noexcept
    {
        return object_class_;
    }

    inline void SetObjectWidth(float32_t width) noexcept
    {
        object_width_ = width;
    }

    inline float32_t GetObjectWidth() const noexcept
    {
        return object_width_;
    }
    inline void SetObjectLength(float32_t length) noexcept
    {
        object_length_ = length;
    }

    inline float32_t GetObjectLength() const noexcept
    {
        return object_length_;
    }

    inline void SetRelativeLongVelocity(float32_t long_velocity) noexcept
    {
        relative_long_velocity_ = long_velocity;
    }

    inline float32_t GetRelativeLongVelocity() const noexcept
    {
        return relative_long_velocity_;
    }

    inline void SetLaneAssignment(uint8_t lane_assignment) noexcept
    {
        lane_assignment_ = lane_assignment;
    }

    inline uint8_t GetLaneAssignment() const noexcept
    {
        return lane_assignment_;
    }

    inline void SetRelativeLatVelocity(float32_t lat_velocity) noexcept
    {
        relative_lat_velocity_ = lat_velocity;
    }

    inline float32_t GetRelativeLatVelocity() const noexcept
    {
        return relative_lat_velocity_;
    }

    inline void SetAbsoluteLongAcc(float32_t abs_long_acc) noexcept
    {
        absolute_long_acc_ = abs_long_acc;
    }

    inline float32_t GetAbsoluteLongAcc() const noexcept
    {
        return absolute_long_acc_;
    }

    inline void SetLongDistanceAcc(float32_t long_distance_acc) noexcept
    {
        long_distance_acc_ = long_distance_acc;
    }

    inline float32_t GetLongDistanceAcc() const noexcept
    {
        return long_distance_acc_;
    }

    inline void SetLateralDistance(float32_t lateral_distance) noexcept
    {
        lateral_distance_ = lateral_distance;
    }

    inline float32_t GetLateralDistance() const noexcept
    {
        return lateral_distance_;
    }

    inline void SetAbsoluteSpeed(float32_t absolute_speed) noexcept
    {
        absolute_speed_ = absolute_speed;
    }

    inline float32_t GetAbsoluteSpeed() const noexcept
    {
        return absolute_speed_;
    }

    inline void SetObjectMotionStatus(uint8_t object_mntion_status) noexcept
    {
        object_motion_status_ = object_mntion_status;
    }

    inline uint8_t GetObjectMotionStatus() const noexcept
    {
        return object_motion_status_;
    }

    inline void SetObjectMotionCategory(uint8_t object_motion_category) noexcept
    {
        object_motion_category_ = object_motion_category;
    }

    inline uint8_t GetObjectMotionCategory() const noexcept
    {
        return object_motion_category_;
    }

    inline void SetBrakeLight(bool_t brake_light) noexcept
    {
        brake_light_ = brake_light;
    }

    inline bool_t GetBrakeLight() const noexcept
    {
        return brake_light_;
    }

    inline void SetTurnIndicatorRight(bool_t turn_indicator_right) noexcept
    {
        turn_indicator_right_ = turn_indicator_right;
    }

    inline bool_t GetTurnIndicatorRight() const noexcept
    {
        return turn_indicator_right_;
    }

    inline void SetTurnIndicatorLeft(bool_t turn_indicator_left) noexcept
    {
        turn_indicator_left_ = turn_indicator_left;
    }

    inline bool_t GetTurnIndicatorLeft() const noexcept
    {
        return turn_indicator_left_;
    }

    inline void SetLightIndicatorValidity(bool_t light_indicator_validity) noexcept
    {
        light_indicator_validity_ = light_indicator_validity;
    }

    inline bool_t GetLightIndicatorValidity() const noexcept
    {
        return light_indicator_validity_;
    }

    inline void SetObjectAngleMid(float32_t object_angle_mid) noexcept
    {
        object_angle_mid_ = object_angle_mid;
    }

    inline float32_t GetObjectAngleMid() const noexcept
    {
        return object_angle_mid_;
    }

    inline void SetObjectAngleRate(float32_t object_angle_rate) noexcept
    {
        object_angle_rate_ = object_angle_rate;
    }

    inline float32_t GetObjectAngleRate() const noexcept
    {
        return object_angle_rate_;
    }

    inline void SetPartAValid(bool_t valid) noexcept
    {
        part_a_valid_ = valid;
    }

    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }

    inline void SetPartBValid(bool_t valid) noexcept
    {
        part_b_valid_ = valid;
    }

    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }

    inline void SetPartCValid(bool_t valid) noexcept
    {
        part_c_valid_ = valid;
    }

    inline bool_t GetPartCValid() const noexcept
    {
        return part_c_valid_;
    }

    inline bool_t IsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_ && part_c_valid_;
    }

private:
    holo::common::Timestamp timestamp_;

    /* part A */
    uint8_t   object_id_;               //! 0|7@1+ (1,0) [0|127] "counter" Vector__XXX
    uint8_t   object_class_;            //! 7|3@1+ (1,0) [0|7] "ENUM" Vector__XXX
    float32_t object_width_;            //! 10|7@1+ (0.05,0) [0|6.35] "m" Vector__XXX
    float32_t object_length_;           //! 17|9@1+ (0.05,0) [0|25.5] "m" Vector__XXX
    float32_t relative_long_velocity_;  //! 26|13@1+ (0.05,-120) [-120|130] "m/s" Vector__XXX
    uint8_t   lane_assignment_;         //! 39|3@1+ (1,0) [0|5] "ENUM" Vector__XXX
    float32_t relative_lat_velocity_;   //! 42|11@1+ (0.05,-50) [-50|50] "m/s" Vector__XXX

    /* part B */
    float32_t absolute_long_acc_;  //! 0|9@1+ (0.05,-12.8) [-12.8|12.75] "m/s2" Vector__XXX
    float32_t long_distance_acc_;  //! 9|13@1+ (0.05,0) [0|350] "m" Vector__XXX
    float32_t lateral_distance_;   //! 22|12@1+ (0.05,-102.4) [-102.4|102.3] "m" Vector__XXX

    /* part C */
    float32_t absolute_speed_;            //! 0|12@1+ (0.05,-100) [-100|100] "m/s" Vector__XXX
    uint8_t   object_motion_status_;      //! 12|3@1+ (1,0) [0|4] "ENUM " Vector__XXX
    uint8_t   object_motion_category_;    //! 15|4@1+ (1,0) [0|12] "ENUM " Vector__XXX
    bool_t    brake_light_;               //! 19|1@1+ (1,0) [0|1] "bool" Vector__XXX
    bool_t    turn_indicator_right_;      //! 20|1@1+ (1,0) [0|1] "bool" Vector__XXX
    bool_t    turn_indicator_left_;       //! 21|1@1+ (1,0) [0|1] "bool" Vector__XXX
    bool_t    light_indicator_validity_;  //! 22|1@1+ (1,0) [0|1] "bool" Vector__XXX
    float32_t object_angle_mid_;          //! 23|14@1+ (0.0002,-1.571) [-1.571|1.571] "rad" Vector__XXX
    float32_t object_angle_rate_;         //! 37|12@1+ (0.002,-2.234) [-2.234|2.2318] "rad/s" Vector__XXX

    bool_t part_a_valid_;  //! part a valid indicator
    bool_t part_b_valid_;  //! part b valid indicator
    bool_t part_c_valid_;  //! part c valid indicator

    static const float32_t kobj_width_min_;
    static const float32_t kobj_height_min_;
    static const float32_t kobj_length_min_;
    static const float32_t kconfidence_;

    static const Classification               kobj_class_remap_table_[8];
    static const holo::obstacle::MotionStatus kmotion_status_remap_table_[8];
    static const holo::obstacle::CutInCutOut  kcut_inout_remap_table_[13][6];
};
}
}  // namespace me8
}  // namespace sensors
#endif
