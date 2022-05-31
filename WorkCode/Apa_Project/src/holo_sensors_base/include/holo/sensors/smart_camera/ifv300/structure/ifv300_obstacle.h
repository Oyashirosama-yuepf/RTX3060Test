/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_obstacle.h
 * @brief A class to describe delphi ifv300 obstacle
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/25
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_IFV300_OBSTACLE_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_IFV300_OBSTACLE_H_

#include <holo/common/coordinate.h>
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
namespace ifv300
{
using holo::common::Classification;

class Ifv300Obstacle
{
public:
    /**
     * @brief Default constructor.
     */
    Ifv300Obstacle()
      : timestamp_()
      , long_pos_(0.0f)
      , lat_pos_(0.0f)
      , long_vel_(0.0f)
      , lat_vel_(0.0f)
      , long_accel_(0.0f)
      , width_(0.0f)
      , height_(0.0f)
      , ttc_(0.0f)
      , object_id_(0)
      , classification_(0)
      , brake_light_ind_(0)
      , turn_ind_(0)
      , cut_in_out_(0)
      , rolling_counter_(0)
      , ped_waist_up_(false)
      , part_a_valid_(false)
      , part_b_valid_(false)
      , part_c_valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other Ifv300Obstacle object.
     */
    Ifv300Obstacle(const Ifv300Obstacle& other) noexcept
      : timestamp_(other.timestamp_)
      , long_pos_(other.long_pos_)
      , lat_pos_(other.lat_pos_)
      , long_vel_(other.long_vel_)
      , lat_vel_(other.lat_vel_)
      , long_accel_(other.long_accel_)
      , width_(other.width_)
      , height_(other.height_)
      , ttc_(other.ttc_)
      , object_id_(other.object_id_)
      , classification_(other.classification_)
      , brake_light_ind_(other.brake_light_ind_)
      , turn_ind_(other.turn_ind_)
      , cut_in_out_(other.cut_in_out_)
      , rolling_counter_(other.rolling_counter_)
      , ped_waist_up_(other.ped_waist_up_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
      , part_c_valid_(other.part_c_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other Ifv300Obstacle object.
     *
     * @return Reference to this object.
     */
    Ifv300Obstacle& operator=(const Ifv300Obstacle& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_       = other.timestamp_;
        long_pos_        = other.long_pos_;
        lat_pos_         = other.lat_pos_;
        long_vel_        = other.long_vel_;
        lat_vel_         = other.lat_vel_;
        long_accel_      = other.long_accel_;
        width_           = other.width_;
        height_          = other.height_;
        ttc_             = other.ttc_;
        object_id_       = other.object_id_;
        classification_  = other.classification_;
        brake_light_ind_ = other.brake_light_ind_;
        turn_ind_        = other.turn_ind_;
        cut_in_out_      = other.cut_in_out_;
        rolling_counter_ = other.rolling_counter_;
        ped_waist_up_    = other.ped_waist_up_;
        part_a_valid_    = other.part_a_valid_;
        part_b_valid_    = other.part_b_valid_;
        part_c_valid_    = other.part_c_valid_;
        return *this;
    }
    /**
     * @brief Convert Ifv300Obstacle to HoloObstacleVision
     *
     * @param output the HoloObstacleVision
     */
    void ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const;
    /**
     * @brief Convert Ifv300Obstacle to HoloObstacleVision with transform
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
     * @brief      Sets the longitudinal position.
     *
     * @param[in]  long_pos  The longitudinal position
     */
    inline void SetLongPos(float32_t long_pos) noexcept
    {
        long_pos_ = long_pos;
    }
    /**
     * @brief      Gets the longitudinal position.
     *
     * @return     The longitudinal position.
     */
    inline float32_t GetLongPos() const noexcept
    {
        return long_pos_;
    }
    /**
     * @brief      Sets the lat position.
     *
     * @param[in]  lat_pos  The lat position
     */
    inline void SetLatPos(float32_t lat_pos) noexcept
    {
        lat_pos_ = lat_pos;
    }
    /**
     * @brief      Gets the lat position.
     *
     * @return     The lat position.
     */
    inline float32_t GetLatPos() const noexcept
    {
        return lat_pos_;
    }
    /**
     * @brief      Sets the longitudinal velocity.
     *
     * @param[in]  long_vel  The longitudinal velocity
     */
    inline void SetLongVel(float32_t long_vel) noexcept
    {
        long_vel_ = long_vel;
    }
    /**
     * @brief      Gets the longitudinal velocity.
     *
     * @return     The longitudinal velocity.
     */
    inline float32_t GetLongVel() const noexcept
    {
        return long_vel_;
    }
    /**
     * @brief      Sets the lat velocity.
     *
     * @param[in]  lat_vel  The lat velocity
     */
    inline void SetLatVel(float32_t lat_vel) noexcept
    {
        lat_vel_ = lat_vel;
    }
    /**
     * @brief      Gets the lat velocity.
     *
     * @return     The lat velocity.
     */
    inline float32_t GetLatVel() const noexcept
    {
        return lat_vel_;
    }
    /**
     * @brief      Sets the longitudinal accel.
     *
     * @param[in]  long_accel  The longitudinal accel
     */
    inline void SetLongAccel(float32_t long_accel) noexcept
    {
        long_accel_ = long_accel;
    }
    /**
     * @brief      Gets the longitudinal accel.
     *
     * @return     The longitudinal accel.
     */
    inline float32_t GetLongAccel() const noexcept
    {
        return long_accel_;
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
     * @brief      Sets the height.
     *
     * @param[in]  height  The height
     */
    inline void SetHeight(float32_t height) noexcept
    {
        height_ = height;
    }
    /**
     * @brief      Gets the height.
     *
     * @return     The height.
     */
    inline float32_t GetHeight() const noexcept
    {
        return height_;
    }
    /**
     * @brief      Sets the time-to-collision value
     *
     * @param[in]  ttc   The new ttc value
     */
    inline void SetTtc(float32_t ttc) noexcept
    {
        ttc_ = ttc;
    }
    /**
     * @brief      Gets the time-to-collision value
     *
     * @return     The ttc value
     */
    inline float32_t GetTtc() const noexcept
    {
        return ttc_;
    }
    /**
     * @brief      Sets the object identifier.
     *
     * @param[in]  object_id  The object identifier
     */
    inline void SetObjectId(uint8_t object_id) noexcept
    {
        object_id_ = object_id;
    }
    /**
     * @brief      Gets the object identifier.
     *
     * @return     The object identifier.
     */
    inline uint8_t GetObjectId() const noexcept
    {
        return object_id_;
    }
    /**
     * @brief      Sets the classification.
     *
     * @param[in]  classification  The classification
     */
    inline void SetClassification(uint8_t classification) noexcept
    {
        classification_ = classification;
    }
    /**
     * @brief      Gets the classification.
     *
     * @return     The classification.
     */
    inline uint8_t GetClassification() const noexcept
    {
        return classification_;
    }
    /**
     * @brief      Sets the brake light ind.
     *
     * @param[in]  brake_light_ind  The brake light ind
     */
    inline void SetBrakeLightInd(uint8_t brake_light_ind) noexcept
    {
        brake_light_ind_ = brake_light_ind;
    }
    /**
     * @brief      Gets the brake light ind.
     *
     * @return     The brake light ind.
     */
    inline uint8_t GetBrakeLightInd() const noexcept
    {
        return brake_light_ind_;
    }
    /**
     * @brief      Sets the turn ind.
     *
     * @param[in]  turn_ind  The turn ind
     */
    inline void SetTurnInd(uint8_t turn_ind) noexcept
    {
        turn_ind_ = turn_ind;
    }
    /**
     * @brief      Gets the turn ind.
     *
     * @return     The turn ind.
     */
    inline uint8_t GetTurnInd() const noexcept
    {
        return turn_ind_;
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
     * @brief      Gets the cut in out type
     *
     * @return     The cut in out.
     */
    inline uint8_t GetCutInOut() const noexcept
    {
        return cut_in_out_;
    }
    /**
     * @brief      Sets the rolling counter.
     *
     * @param[in]  rolling_counter  The rolling counter 0 ~ 3
     */
    inline void SetRollingCounter(uint8_t rolling_counter) noexcept
    {
        rolling_counter_ = rolling_counter;
    }
    /**
     * @brief      Gets the rolling counter.
     *
     * @return     The rolling counter 0 ~ 3
     */
    inline uint8_t GetRollingCounter() const noexcept
    {
        return rolling_counter_;
    }
    inline void SetPedWaistUp(bool_t ped_waist_up) noexcept
    {
        ped_waist_up_ = ped_waist_up;
    }
    /**
     * @brief      Gets the ped waist up ind
     *
     * @return     true if obj is ped waist up, else false
     */
    inline bool_t GetPedWaistUp() const noexcept
    {
        return ped_waist_up_;
    }
    /**
     * @brief      Sets the part a valid.
     *
     * @param[in]  valid  The valid
     */
    inline void SetPartAValid(bool_t valid) noexcept
    {
        part_a_valid_ = valid;
    }
    /**
     * @brief      Gets the part a valid.
     *
     * @return     The part a valid.
     */
    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }
    /**
     * @brief      Sets the part b valid.
     *
     * @param[in]  valid  The valid
     */
    inline void SetPartBValid(bool_t valid) noexcept
    {
        part_b_valid_ = valid;
    }
    /**
     * @brief      Gets the part b valid.
     *
     * @return     The part b valid.
     */
    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }
    /**
     * @brief      Sets the part c valid.
     *
     * @param[in]  valid  The valid
     */
    inline void SetPartCValid(bool_t valid) noexcept
    {
        part_c_valid_ = valid;
    }
    /**
     * @brief      Gets the part c valid.
     *
     * @return     The part c valid.
     */
    inline bool_t GetPartCValid() const noexcept
    {
        return part_c_valid_;
    }
    /**
     * @brief Check is this obstacle is valid
     *
     * @return true if the obstacle is valid otherwise return false
     */
    inline bool_t IsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_ && part_c_valid_;
    }

private:
    holo::common::Timestamp timestamp_;

    float32_t long_pos_;         //! long distance   | (0.03125,0) [0|255] "m"
    float32_t lat_pos_;          //! lat distance    | (0.0625,-128) [-128|127.9375] "m"
    float32_t long_vel_;         //! long velocity   | (0.0625,-128) [-128|127.9375] "m/s"
    float32_t lat_vel_;          //! lat velocity    | (0.0625,-128) [-128|127.9375] "m/s"
    float32_t long_accel_;       //! long accel      | (0.0078125,-20) [-20|20] "m/s^2"
    float32_t width_;            //! width           | (0.1,0) [0|6] "m"
    float32_t height_;           //! height          | (0.1,0) [0|3] "m"
    float32_t ttc_;              //! time to collis* | (0.01,0) [0|7] "s"
    uint8_t   object_id_;        //! obj index       | (1,0) [0|15] "obs"
    uint8_t   classification_;   //! class           | [0,10]
    uint8_t   brake_light_ind_;  //! brake light ind | 2 "brake light is steady active" 1 "no brake light is active" 0
                                 //! "unknown"
    uint8_t turn_ind_;  //! turn ind        | 3 "unknown" 2 "right turn indicator active" 1 "left turn indicator active"
                        //! 0 "no turn indicator active"
    uint8_t cut_in_out_;  //! cut ind         | 7 "reserved" 6 "reserved" 5 "reserved" 4 "cut out" 3 "cut in" 2 "out
                          //! host lane" 1 "in host lane" 0 "undetermined"
    uint8_t rolling_counter_;  //! roll counter 1  | (1,0) [0|3] ""
    bool_t  ped_waist_up_;     //! ped waist up    | 1 "false" 0 "true"
    bool_t  part_a_valid_;     //! part a valid indicator
    bool_t  part_b_valid_;     //! part b valid indicator
    bool_t  part_c_valid_;     //! part c valid indicator

    static const uint32_t       kobj_number_ = 16;
    static const float32_t      kobj_width_min_;
    static const float32_t      kobj_length_;
    static const float32_t      kobj_height_min_;
    static const float32_t      kconfidence_;
    static const Classification kobj_class_remap_table_[16];
};

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo

#endif
