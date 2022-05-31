/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_obstacle.h
 * @brief A class to describe horizon matrix2 obstacle
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/21
 */

#ifndef HOLO_SENSORS_COMMON_SMART_CAMERA_HORIZON_MATRIX2_OBSTACLE_H_
#define HOLO_SENSORS_COMMON_SMART_CAMERA_HORIZON_MATRIX2_OBSTACLE_H_

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
namespace horizon_matrix2
{
using holo::common::Classification;
using holo::obstacle::MotionStatus;

class HorizonMatrix2Obstacle
{
public:
    /**
     * @brief Default constructor.
     */
    HorizonMatrix2Obstacle()
      : timestamp_()
      , id_(0)
      , type_(0)
      , ped_subtype_(0)
      , vehicle_subtype_(0)
      , status_(0)
      , move_in_and_out_(0)
      , pos_x_(0.0f)
      , pos_y_(0.0f)
      , vel_x_(0.0f)
      , vel_y_(0.0f)
      , accel_x_(0.0f)
      , length_(0.0f)
      , width_(0.0f)
      , angle_rate_(0.0f)
      , vehicle_angle_(0.0f)
      , valid_(false)
      , part_a_valid_(false)
      , part_b_valid_(false)
      , part_c_valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other HorizonMatrix2Obstacle object.
     */
    HorizonMatrix2Obstacle(const HorizonMatrix2Obstacle& other) noexcept
      : timestamp_(other.timestamp_)
      , id_(other.id_)
      , type_(other.type_)
      , ped_subtype_(other.ped_subtype_)
      , vehicle_subtype_(other.vehicle_subtype_)
      , status_(other.status_)
      , move_in_and_out_(other.move_in_and_out_)
      , pos_x_(other.pos_x_)
      , pos_y_(other.pos_y_)
      , vel_x_(other.vel_x_)
      , vel_y_(other.vel_y_)
      , accel_x_(other.accel_x_)
      , length_(other.length_)
      , width_(other.width_)
      , angle_rate_(other.angle_rate_)
      , vehicle_angle_(other.vehicle_angle_)
      , valid_(other.valid_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
      , part_c_valid_(other.part_c_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other HorizonMatrix2Obstacle object.
     *
     * @return Reference to this object.
     */
    HorizonMatrix2Obstacle& operator=(const HorizonMatrix2Obstacle& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_       = other.timestamp_;
        id_              = other.id_;
        type_            = other.type_;
        ped_subtype_     = other.ped_subtype_;
        vehicle_subtype_ = other.vehicle_subtype_;
        status_          = other.status_;
        move_in_and_out_ = other.move_in_and_out_;
        pos_x_           = other.pos_x_;
        pos_y_           = other.pos_y_;
        vel_x_           = other.vel_x_;
        vel_y_           = other.vel_y_;
        accel_x_         = other.accel_x_;
        length_          = other.length_;
        width_           = other.width_;
        angle_rate_      = other.angle_rate_;
        vehicle_angle_   = other.vehicle_angle_;
        valid_           = other.valid_;
        part_a_valid_    = other.part_a_valid_;
        part_b_valid_    = other.part_b_valid_;
        part_c_valid_    = other.part_c_valid_;
        return *this;
    }
    /**
     * @brief Convert HorizonMatrix2Obstacle to HoloObstacleVision
     *
     * @param output the HoloObstacleVision
     */
    void ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const;
    /**
     * @brief Convert HorizonMatrix2Obstacle to HoloObstacleVision with transform
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
        timestamp_ = timestamp;
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
    inline void SetId(uint8_t id) noexcept
    {
        id_ = id;
    }
    inline uint8_t GetId() const noexcept
    {
        return id_;
    }
    inline uint8_t GetType() const noexcept
    {
        return type_;
    }
    inline void SetType(uint8_t type) noexcept
    {
        type_ = type;
    }
    inline uint8_t GetPedSubtype() const noexcept
    {
        return ped_subtype_;
    }
    inline void SetPedSubtype(uint8_t ped_subtype) noexcept
    {
        ped_subtype_ = ped_subtype;
    }
    inline uint8_t GetVehicleSubtype() const noexcept
    {
        return vehicle_subtype_;
    }
    inline void SetVehicleSubtype(uint8_t vehicle_subtype) noexcept
    {
        vehicle_subtype_ = vehicle_subtype;
    }
    inline uint8_t GetStatus() const noexcept
    {
        return status_;
    }
    inline void SetStatus(uint8_t status) noexcept
    {
        status_ = status;
    }
    inline uint8_t GetMoveInOut() const noexcept
    {
        return move_in_and_out_;
    }
    inline void SetMoveInOut(uint8_t move_in_and_out) noexcept
    {
        move_in_and_out_ = move_in_and_out;
    }
    inline float32_t GetPosX() const noexcept
    {
        return pos_x_;
    }
    inline void SetPosX(float32_t posx) noexcept
    {
        pos_x_ = posx;
    }
    inline float32_t GetPosY() const noexcept
    {
        return pos_y_;
    }
    inline void SetPosY(float32_t posy) noexcept
    {
        pos_y_ = posy;
    }
    inline float32_t GetVelX() const noexcept
    {
        return vel_x_;
    }
    inline void SetVelX(float32_t velx) noexcept
    {
        vel_x_ = velx;
    }
    inline float32_t GetVelY() const noexcept
    {
        return vel_y_;
    }
    inline void SetVelY(float32_t vely) noexcept
    {
        vel_y_ = vely;
    }
    inline float32_t GetAccelX() const noexcept
    {
        return accel_x_;
    }
    inline void SetAccelX(float32_t accel_x) noexcept
    {
        accel_x_ = accel_x;
    }
    inline float32_t GetLength() const noexcept
    {
        return length_;
    }
    inline void SetLength(float32_t length) noexcept
    {
        length_ = length;
    }
    inline float32_t GetWidth() const noexcept
    {
        return width_;
    }
    inline void SetWidth(float32_t width) noexcept
    {
        width_ = width;
    }
    inline float32_t GetAngleRate() const noexcept
    {
        return angle_rate_;
    }
    inline void SetAngleRate(float32_t angle_rate) noexcept
    {
        angle_rate_ = angle_rate;
    }
    inline float32_t GetVehicleAngle() const noexcept
    {
        return vehicle_angle_;
    }
    inline void SetVehicleAngle(float32_t vehicle_angle) noexcept
    {
        vehicle_angle_ = vehicle_angle;
    }
    inline void SetValid(uint8_t valid) noexcept
    {
        valid_ = valid;
    }
    inline uint8_t GetValid() const noexcept
    {
        return valid_;
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
    inline bool_t IsAllPartsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_ && part_c_valid_;
    }

private:
    holo::common::Timestamp timestamp_;

    uint8_t   id_;                   //!  0| 8@1+ (1,0) [0|63] "NA" Matrix
    uint8_t   type_ : 2;             //! 52| 2@1+ (1,0) [0|3] "enum" Matrix
    uint8_t   ped_subtype_ : 2;      //! 37| 2@1+ (1,0) [0|3] "Enum" Matrix
    uint8_t   vehicle_subtype_ : 4;  //! 54| 4@1+ (1,0) [0|15] "enum" Matrix
    uint8_t   status_;               //! 58| 3@1+ (1,0) [0|7] "enum" Matrix
    uint8_t   move_in_and_out_;      //! 37| 3@1+ (1,0) [0|4] "enum" Matrix
    float32_t pos_x_;                //!  8|13@1+ (0.0625,-256) [-256|255] "m" Matrix
    float32_t pos_y_;                //! 21|13@1+ (0.0625,-256) [-256|255] "m" Matrix
    float32_t vel_x_;                //! 40|12@1- (0.0625,0) [-127.93|127.93] "m/sec" Matrix
    float32_t vel_y_;                //! 16|12@1- (0.0625,0) [-127.93|127.93] "m/sec" Matrix
    float32_t accel_x_;              //! 28|10@1- (0.03,0) [-14.97|14.97] "m/s square" Matrix
    float32_t length_;               //!  0| 8@1+ (0.5,0) [0|31.5] "m" Matrix
    float32_t width_;                //!  8| 8@1+ (0.05,0) [0|12.5] "m" Matrix
    float32_t angle_rate_;           //!  0|16@1- (0.01,0) [-327.68|327.67] "degree" Matrix
    float32_t vehicle_angle_;        //! 43|16@1- (0.01,0) [-327.68|327.67] "degree" Matrix
    bool_t    valid_;                //! 62| 2@1+ (1,0) [0|2] "bool" Matrix
    bool_t    part_a_valid_;         //! part a valid indicator
    bool_t    part_b_valid_;         //! part b valid indicator
    bool_t    part_c_valid_;         //! part c valid indicator

    static const Classification          type_remap_table_const_[4];
    static const Classification::SubType vehicle_subtype_remap_table_const_[16];
    static const MotionStatus            motion_status_remap_table_const_[8];
};

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo

#endif
