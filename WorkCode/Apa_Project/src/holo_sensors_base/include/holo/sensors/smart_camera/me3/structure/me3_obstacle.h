/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_obstacle.h
 * @brief A class to describe mobileye obstacle
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/01/15
 */

#ifndef HOLO_SENSORS_COMMON_MOBILEYE_OBSTACLE_H_
#define HOLO_SENSORS_COMMON_MOBILEYE_OBSTACLE_H_

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
namespace mobileye
{
using holo::common::Classification;
using holo::obstacle::CutInCutOut;
using holo::obstacle::MotionStatus;
class MobileyeObstacle
{
public:
    /**
     * @brief Default constructor.
     */
    MobileyeObstacle()
      : timestamp_()
      , longitudinal_dist_(0.0f)
      , lateral_dist_(0.0f)
      , longitudinal_velocity_(0.0f)
      , lateral_velocity_(0.0f)
      , acceleration_(0.0f)
      , width_(0.0f)
      , angle_left_(0.0f)
      , angle_right_(0.0f)
      , angle_rate_mean_(0.0f)
      , object_age_(0)
      , id_(0)
      , object_class_(0)
      , motion_status_(0)
      , cut_in_out_(0)
      , replaced_(false)
      , cipv_flag_(false)
      , part_0_valid_(false)
      , part_1_valid_(false)
      , part_2_valid_(false)
      , part_3_valid_(false)

    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other MobileyeObstacle object.
     */
    MobileyeObstacle(const MobileyeObstacle& other) noexcept
      : timestamp_(other.timestamp_)
      , longitudinal_dist_(other.longitudinal_dist_)
      , lateral_dist_(other.lateral_dist_)
      , longitudinal_velocity_(other.longitudinal_velocity_)
      , lateral_velocity_(other.lateral_velocity_)
      , acceleration_(other.acceleration_)
      , width_(other.width_)
      , angle_left_(other.angle_left_)
      , angle_right_(other.angle_right_)
      , angle_rate_mean_(other.angle_rate_mean_)
      , object_age_(other.object_age_)
      , id_(other.id_)
      , object_class_(other.object_class_)
      , motion_status_(other.motion_status_)
      , cut_in_out_(other.cut_in_out_)
      , replaced_(other.replaced_)
      , cipv_flag_(other.cipv_flag_)
      , part_0_valid_(other.part_0_valid_)
      , part_1_valid_(other.part_1_valid_)
      , part_2_valid_(other.part_2_valid_)
      , part_3_valid_(other.part_3_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other MobileyeObstacle object.
     *
     * @return Reference to this object.
     */
    MobileyeObstacle& operator=(const MobileyeObstacle& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_             = other.timestamp_;
        longitudinal_dist_     = other.longitudinal_dist_;
        lateral_dist_          = other.lateral_dist_;
        longitudinal_velocity_ = other.longitudinal_velocity_;
        lateral_velocity_      = other.lateral_velocity_;
        acceleration_          = other.acceleration_;
        width_                 = other.width_;
        angle_left_            = other.angle_left_;
        angle_right_           = other.angle_right_;
        angle_rate_mean_       = other.angle_rate_mean_;
        object_age_            = other.object_age_;
        id_                    = other.id_;
        object_class_          = other.object_class_;
        motion_status_         = other.motion_status_;
        cut_in_out_            = other.cut_in_out_;
        replaced_              = other.replaced_;
        cipv_flag_             = other.cipv_flag_;
        part_0_valid_          = other.part_0_valid_;
        part_1_valid_          = other.part_1_valid_;
        part_2_valid_          = other.part_2_valid_;
        part_3_valid_          = other.part_3_valid_;
        return *this;
    }
    /**
     * @brief Convert MobileyeObstacle to HoloObstacleVision
     *
     * @param output the HoloObstacleVision
     */
    void ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const;
    /**
     * @brief Convert MobileyeObstacle to HoloObstacleVision with transform
     *
     * @param input the extrinsic between mpc and target coord
     * @param output the HoloObstacleVision
     */
    void ConvertToHoloObstacleWithTransform(holo::obstacle::ObstacleVisionT<float32_t>& output,
                                            const holo::common::Extrinsicf&             extrinsic) const;
    /**
     * @brief Set time stamp
     *
     * @param[in] time_stamp
     */
    inline void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }
    /**
     * @brief Get time stamp
     *
     * @return timestamp_
     */
    inline holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }
    /**
     * @brief      Sets the longitudinal distance.
     *
     * @param[in]  longitudinal_dist  The longitudinal distance
     */
    inline void SetLongitudinalDist(float32_t longitudinal_dist) noexcept
    {
        longitudinal_dist_ = longitudinal_dist;
    }
    /**
     * @brief      Gets the longitudinal distance.
     *
     * @return     The longitudinal distance.
     */
    inline float32_t GetLongitudinalDist() const noexcept
    {
        return longitudinal_dist_;
    }
    /**
     * @brief      Sets the lateral distance.
     *
     * @param[in]  lateral_dist  The lateral distance
     */
    inline void SetLateralDist(float32_t lateral_dist) noexcept
    {
        lateral_dist_ = lateral_dist;
    }
    /**
     * @brief      Gets the lateral distance.
     *
     * @return     The lateral distance.
     */
    inline float32_t GetLateralDist() const noexcept
    {
        return lateral_dist_;
    }
    /**
     * @brief      Sets the longitudinal velocity.
     *
     * @param[in]  longitudinal_velocity  The longitudinal velocity
     */
    inline void SetLongitudinalVelocity(float32_t longitudinal_velocity) noexcept
    {
        longitudinal_velocity_ = longitudinal_velocity;
    }
    /**
     * @brief      Gets the longitudinal velocity.
     *
     * @return     The longitudinal velocity.
     */
    inline float32_t GetLongitudinalVelocity() const noexcept
    {
        return longitudinal_velocity_;
    }
    /**
     * @brief      Sets the lateral velocity.
     *
     * @param[in]  lateral_velocity  The lateral velocity
     */
    inline void SetLateralVelocity(float32_t lateral_velocity) noexcept
    {
        lateral_velocity_ = lateral_velocity;
    }
    /**
     * @brief      Gets the lateral velocity.
     *
     * @return     The lateral velocity.
     */
    inline float32_t GetLateralVelocity() const noexcept
    {
        return lateral_velocity_;
    }
    /**
     * @brief      Sets the acceleration.
     *
     * @param[in]  acceleration  The acceleration
     */
    inline void SetAcceleration(float32_t acceleration) noexcept
    {
        acceleration_ = acceleration;
    }
    /**
     * @brief      Gets the acceleration.
     *
     * @return     The acceleration.
     */
    inline float32_t GetAcceleration() const noexcept
    {
        return acceleration_;
    }
    /**
     * @brief      Sets the width.
     *
     * @param[in]  width  The width
     */
    inline void SetWidth(float32_t width) noexcept
    {
        width_ = width;
    }
    /**
     * @brief      Gets the width.
     *
     * @return     The width.
     */
    inline float32_t GetWidth() const noexcept
    {
        return width_;
    }
    /**
     * @brief      Sets the angle left.
     *
     * @param[in]  angle_left  The angle left
     */
    inline void SetAngleLeft(float32_t angle_left) noexcept
    {
        angle_left_ = angle_left;
    }
    /**
     * @brief      Gets the angle left.
     *
     * @return     The angle left.
     */
    inline float32_t GetAngleLeft() const noexcept
    {
        return angle_left_;
    }
    /**
     * @brief      Sets the angle right.
     *
     * @param[in]  angle_right  The angle right
     */
    inline void SetAngleRight(float32_t angle_right) noexcept
    {
        angle_right_ = angle_right;
    }
    /**
     * @brief      Gets the angle right.
     *
     * @return     The angle right.
     */
    inline float32_t GetAngleRight() const noexcept
    {
        return angle_right_;
    }
    /**
     * @brief      Sets the angle rate mean.
     *
     * @param[in]  angle_rate_mean  The angle rate mean
     */
    inline void SetAngleRateMean(float32_t angle_rate_mean) noexcept
    {
        angle_rate_mean_ = angle_rate_mean;
    }
    /**
     * @brief      Gets the angle rate mean.
     *
     * @return     The angle rate mean.
     */
    inline float32_t GetAngleRateMean() const noexcept
    {
        return angle_rate_mean_;
    }
    /**
     * @brief      Sets the object age.
     *
     * @param[in]  object_age  The object age
     */
    inline void SetObjectAge(uint16_t object_age) noexcept
    {
        object_age_ = object_age;
    }
    /**
     * @brief      Gets the object age.
     *
     * @return     The object age.
     */
    inline uint16_t GetObjectAge() const noexcept
    {
        return object_age_;
    }
    /**
     * @brief      Sets the identifier.
     *
     * @param[in]  id    The new value
     */
    inline void SetId(uint8_t id) noexcept
    {
        id_ = id;
    }
    /**
     * @brief      Gets the identifier.
     *
     * @return     The identifier.
     */
    inline uint8_t GetId() const noexcept
    {
        return id_;
    }
    /**
     * @brief      Sets the object class.
     *
     * @param[in]  object_class  The object class
     */
    inline void SetObjectClass(uint8_t object_class) noexcept
    {
        object_class_ = object_class;
    }
    /**
     * @brief      Gets the object class.
     *
     * @return     The object class.
     */
    inline uint8_t GetObjectClass() const noexcept
    {
        return object_class_;
    }
    /**
     * @brief      Sets the motion status.
     *
     * @param[in]  motion_status  The motion status
     */
    inline void SetMotionStatus(uint8_t motion_status) noexcept
    {
        motion_status_ = motion_status;
    }
    /**
     * @brief      Gets the motion status.
     *
     * @return     The motion status.
     */
    inline uint8_t GetMotionStatus() const noexcept
    {
        return motion_status_;
    }
    /**
     * @brief      Sets the cut in out.
     *
     * @param[in]  cut_in_out  The cut in out
     */
    inline void SetCutInOut(uint8_t cut_in_out) noexcept
    {
        cut_in_out_ = cut_in_out;
    }
    /**
     * @brief      Gets the cut in out.
     *
     * @return     The cut in out.
     */
    inline uint8_t GetCutInOut() const noexcept
    {
        return cut_in_out_;
    }
    /**
     * @brief      Sets the replaced.
     *
     * @param[in]  replaced  Indicates if replaced
     */
    inline void SetReplaced(bool_t replaced) noexcept
    {
        replaced_ = replaced;
    }
    /**
     * @brief      Gets the replaced.
     *
     * @return     The replaced.
     */
    inline bool_t GetReplaced() const noexcept
    {
        return replaced_;
    }
    /**
     * @brief      Sets the cipv flag.
     *
     * @param[in]  cipv_flag  The cipv flag
     */
    inline void SetCipvFlag(bool_t cipv_flag) noexcept
    {
        cipv_flag_ = cipv_flag;
    }
    /**
     * @brief      Gets the cipv flag.
     *
     * @return     The cipv flag.
     */
    inline bool_t GetCipvFlag() const noexcept
    {
        return cipv_flag_;
    }
    /**
     * @brief      Sets the part 0 valid.
     *
     * @param[in]  part_0_valid  The part 0 valid
     */
    inline void SetPart0Valid(bool_t part_0_valid) noexcept
    {
        part_0_valid_ = part_0_valid;
    }
    /**
     * @brief      Gets the part 0 valid.
     *
     * @return     The part 0 valid.
     */
    inline bool_t GetPart0Valid() const noexcept
    {
        return part_0_valid_;
    }
    /**
     * @brief      Sets the part 1 valid.
     *
     * @param[in]  part_1_valid  The part 1 valid
     */
    inline void SetPart1Valid(bool_t part_1_valid) noexcept
    {
        part_1_valid_ = part_1_valid;
    }
    /**
     * @brief      Gets the part 1 valid.
     *
     * @return     The part 1 valid.
     */
    inline bool_t GetPart1Valid() const noexcept
    {
        return part_1_valid_;
    }
    /**
     * @brief      Sets the part 2 valid.
     *
     * @param[in]  part_2_valid  The part 2 valid
     */
    inline void SetPart2Valid(bool_t part_2_valid) noexcept
    {
        part_2_valid_ = part_2_valid;
    }
    /**
     * @brief      Gets the part 2 valid.
     *
     * @return     The part 2 valid.
     */
    inline bool_t GetPart2Valid() const noexcept
    {
        return part_2_valid_;
    }
    /**
     * @brief      Sets the part 3 valid.
     *
     * @param[in]  part_3_valid  The part 3 valid
     */
    inline void SetPart3Valid(bool_t part_3_valid) noexcept
    {
        part_3_valid_ = part_3_valid;
    }
    /**
     * @brief      Gets the part 3 valid.
     *
     * @return     The part 3 valid.
     */
    inline bool_t GetPart3Valid() const noexcept
    {
        return part_3_valid_;
    }
    /**
     * @brief Check is this obstacle is valid
     *
     * @return true if the obstacle is valid otherwise return false
     */
    inline bool_t IsAllPartsValid() const noexcept
    {
        return part_0_valid_ && part_1_valid_ && part_2_valid_ && part_3_valid_;
    }

private:
    /* time stamp */
    holo::common::Timestamp timestamp_;  //! timestamp
    /* members */
    float32_t longitudinal_dist_;      //! 32|12@1+ (0.05,0) [0|204.75] "m" Vector__XXX
    float32_t lateral_dist_;           //! 32|12@1+ (0.05,-102.4) [-102.4|102.35] "m" Vector__XXX
    float32_t longitudinal_velocity_;  //! 32|13@1+ (0.05,-128) [-128|128] "m/s" Vector__XXX
    float32_t lateral_velocity_;       //! 0|9@1+ (0.05,-12.8) [-12.8|12.75] "m/s" Vector__XXX
    float32_t acceleration_;           //! 16|9@1+ (0.05,-12.8) [-12.8|12.75] "m/s2" Vector__XXX
    float32_t width_;                  //! 48|7@1+ (0.05,0) [0|6.35] "m" Vector__XXX
    float32_t angle_left_;             //! 48|13@1+ (0.0002,-0.8192) [-0.8192|0.819] "rad" Vector__XXX
    float32_t angle_right_;            //! 0|13@1+ (0.0002,-0.8192) [-0.8192|0.819] "rad" Vector__XXX
    float32_t angle_rate_mean_;        //! 4|12@1+ (0.002,-2.234) [-2.234|2.2318] "rad/s" Vector__XXX
    uint16_t  object_age_;             //! 20|11@1+ (1,0) [0|2047] "frames" Vector__XXX
    uint8_t   id_;                     //! 24|7@1+ (1,0) [1|63] "counter" Vector__XXX
    uint8_t   object_class_;           //! 21|3@1+ (1,0) [0|6] "ENUM" Vector__XXX
    uint8_t   motion_status_;          //! 44|4@1+ (1,0) [0|8] "ENUM" Vector__XXX
    uint8_t   cut_in_out_;             //! 0|4@1+ (1,0) [0|8] "ENUM" Vector__XXX
    bool_t    replaced_;               //! 41|1@1+ (1,0) [0|1] "bool" Vector__XXX
    bool_t    cipv_flag_;              //! 40|1@1+ (1,0) [0|1] "bool" Vector__XXX
    /* valid inds */
    bool_t part_0_valid_;  //! part 0 valid indicator
    bool_t part_1_valid_;  //! part 1 valid indicator
    bool_t part_2_valid_;  //! part 2 valid indicator
    bool_t part_3_valid_;  //! part 3 valid indicator
    /* remap tables */
    static const float32_t      kconfidence_;
    static const Classification kclass_remap_table_[8];
    static const MotionStatus   kmotion_status_remap_table_[16];
    static const CutInCutOut    kcut_inout_remap_table_[16];
};

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo

#endif
