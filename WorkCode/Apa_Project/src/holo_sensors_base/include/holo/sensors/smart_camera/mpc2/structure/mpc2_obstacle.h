/**
 * @file bosch_mpc_obstacle.h
 * @brief This header file defines the structure of obstacle from bosch mpc.
 * @author
 * @date 2019-12-3
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_SENSORS_COMMON_BOSCH_MPC_OBSTACLE_H_
#define HOLO_SENSORS_COMMON_BOSCH_MPC_OBSTACLE_H_

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
namespace bosch_mpc
{
using holo::common::Classification;

class BoschMpcObstacle
{
public:
    /**
     * @brief Default constructor.
     */
    BoschMpcObstacle()
      : timestamp_()
      , long_dist_(0.0f)
      , angle_center_(0.0f)
      , classification_(0u)
      , angle_width_(0.0f)
      , confidence_(0.0f)
      , angle_speed_(0.0f)
      , angle_overlap_egolane_left_(0.0f)
      , angle_overlap_egolane_right_(0.0f)
      , inv_ttc_(0.0f)
      , age_(0)
      , angle_edge_left_(0.0f)
      , angle_edge_right_(0.0f)
      , id_(0u)
      , long_velocity_(0.0f)
      , part_a_valid_(false)
      , part_b_valid_(false)
      , part_c_valid_(false)
      , part_d_valid_(false)
      , part_e_valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other BoschMpcObstacle object.
     */
    BoschMpcObstacle(const BoschMpcObstacle& other) noexcept
      : timestamp_(other.timestamp_)
      , long_dist_(other.long_dist_)
      , angle_center_(other.angle_center_)
      , classification_(other.classification_)
      , angle_width_(other.angle_width_)
      , confidence_(other.confidence_)
      , angle_speed_(other.angle_speed_)
      , angle_overlap_egolane_left_(other.angle_overlap_egolane_left_)
      , angle_overlap_egolane_right_(other.angle_overlap_egolane_right_)
      , inv_ttc_(other.inv_ttc_)
      , age_(other.age_)
      , angle_edge_left_(other.angle_edge_left_)
      , angle_edge_right_(other.angle_edge_right_)
      , id_(other.id_)
      , long_velocity_(other.long_velocity_)
      , part_a_valid_(other.part_a_valid_)
      , part_b_valid_(other.part_b_valid_)
      , part_c_valid_(other.part_c_valid_)
      , part_d_valid_(other.part_d_valid_)
      , part_e_valid_(other.part_e_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other BoschMpcObstacle object.
     *
     * @return Reference to this object.
     */
    BoschMpcObstacle& operator=(const BoschMpcObstacle& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_                   = other.timestamp_;
        long_dist_                   = other.long_dist_;
        angle_center_                = other.angle_center_;
        classification_              = other.classification_;
        angle_width_                 = other.angle_width_;
        confidence_                  = other.confidence_;
        angle_speed_                 = other.angle_speed_;
        angle_overlap_egolane_left_  = other.angle_overlap_egolane_left_;
        angle_overlap_egolane_right_ = other.angle_overlap_egolane_right_;
        inv_ttc_                     = other.inv_ttc_;
        age_                         = other.age_;
        angle_edge_left_             = other.angle_edge_left_;
        angle_edge_right_            = other.angle_edge_right_;
        id_                          = other.id_;
        long_velocity_               = other.long_velocity_;
        part_a_valid_                = other.part_a_valid_;
        part_b_valid_                = other.part_b_valid_;
        part_c_valid_                = other.part_c_valid_;
        part_d_valid_                = other.part_d_valid_;
        part_e_valid_                = other.part_e_valid_;
        return *this;
    }
    /**
     * @brief Convert BoschMpcObstacle to HoloObstacleVision
     *
     * @param output the HoloObstacleVision
     */
    void ConvertToHoloObstacle(holo::obstacle::ObstacleVisionT<float32_t>& output) const;
    /**
     * @brief Convert BoschMpcObstacle to HoloObstacleVision with transform
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
     * @brief Set longitudial distance
     *
     * @param[in] long_dist
     */
    inline void SetLongDist(float32_t long_dist) noexcept
    {
        long_dist_ = long_dist;
    }
    /**
     * @brief Get longitudial distance
     *
     * @return long_dist_
     */
    inline float32_t GetLongDist() const noexcept
    {
        return long_dist_;
    }
    /**
     * @brief Get angle center
     *
     * @return angle_center_
     */
    inline float32_t GetAngleCenter() const noexcept
    {
        return angle_center_;
    }
    /**
     * @brief Set angle center
     *
     * @param[in] angle_center
     */
    inline void SetAngleCenter(float32_t angle_center) noexcept
    {
        angle_center_ = angle_center;
    }
    /**
     * @brief Get classification
     *
     * @return classification_
     */
    inline uint8_t GetClassification() const noexcept
    {
        return classification_;
    }
    /**
     * @brief Set classification
     *
     * @param[in] classification
     */
    inline void SetClassification(uint8_t classification) noexcept
    {
        classification_ = classification;
    }
    /**
     * @brief Get angle width
     *
     * @return angle_width_
     */
    inline float32_t GetAngleWidth() const noexcept
    {
        return angle_width_;
    }
    /**
     * @brief Set angle width
     *
     * @param[in] angle_width_
     */
    inline void SetAngleWidth(float32_t angle_width) noexcept
    {
        angle_width_ = angle_width;
    }
    /**
     * @brief Get confidence
     *
     * @return confidence_
     */
    inline float32_t GetConfidence() const noexcept
    {
        return confidence_;
    }
    /**
     * @brief Set confidence
     *
     * @param[in] confidence
     */
    inline void SetConfidence(float32_t confidence) noexcept
    {
        confidence_ = confidence;
    }
    /**
     * @brief Get angle speed
     *
     * @return angle_speed_
     */
    inline float32_t GetAngleSpeed() const noexcept
    {
        return angle_speed_;
    }
    /**
     * @brief Set angle speed
     *
     * @param[in] angle_speed
     */
    inline void SetAngleSpeed(float32_t angle_speed) noexcept
    {
        angle_speed_ = angle_speed;
    }
    /**
     * @brief Get angle overlap ego lane left
     *
     * @return angle_overlap_egolane_left_
     */
    inline float32_t GetAngleOverlapEgolaneLeft() const noexcept
    {
        return angle_overlap_egolane_left_;
    }
    /**
     * @brief Set angle overlap egolane left
     *
     * @param[in] angle_overlap_egolane_left
     */
    inline void SetAngleOverlapEgolaneLeft(float32_t angle_overlap_egolane_left) noexcept
    {
        angle_overlap_egolane_left_ = angle_overlap_egolane_left;
    }
    /**
     * @brief Get angle overlap ego lane right
     *
     * @return angle_overlap_egolane_right_
     */
    inline float32_t GetAngleOverlapEgolaneRight() const noexcept
    {
        return angle_overlap_egolane_right_;
    }
    /**
     * @brief Set angle overlap egolane right
     *
     * @param[in] angle_overlap_egolane_right
     */
    inline void SetAngleOverlapEgolaneRight(float32_t angle_overlap_egolane_right) noexcept
    {
        angle_overlap_egolane_right_ = angle_overlap_egolane_right;
    }
    /**
     * @brief Get inverse time to collision
     *
     * @return inv_ttc_
     */
    inline float32_t GetInvTTC() const noexcept
    {
        return inv_ttc_;
    }
    /**
     * @brief Get inverse time to collision
     *
     * @param[in] inv_ttc
     */
    inline void SetInvTTC(float32_t inv_ttc) noexcept
    {
        inv_ttc_ = inv_ttc;
    }
    /**
     * @brief Get age
     *
     * @return age_
     */
    inline uint16_t GetAge() const noexcept
    {
        return age_;
    }
    /**
     * @brief Set age
     *
     * @param[in] age
     */
    inline void SetAge(uint16_t age) noexcept
    {
        age_ = age;
    }
    /**
     * @brief Get angle edge left
     *
     * @return angle_edge_left_
     */
    inline float32_t GetAngleEdgeLeft() const noexcept
    {
        return angle_edge_left_;
    }
    /**
     * @brief Set angle edge left
     *
     * @param[in] angle edge left
     */
    inline void SetAngleEdgeLeft(float32_t angle_edge_left) noexcept
    {
        angle_edge_left_ = angle_edge_left;
    }
    /**
     * @brief Get angle edge right
     *
     * @return angle_edge_right_
     */
    inline float32_t GetAngleEdgeRight() const noexcept
    {
        return angle_edge_right_;
    }
    /**
     * @brief Set angle edge right
     *
     * @param[in] angle_edge_right
     */
    inline void SetAngleEdgeRight(float32_t angle_edge_right) noexcept
    {
        angle_edge_right_ = angle_edge_right;
    }
    /**
     * @brief Get longitudial velocity
     *
     * @return long_velocity_
     */
    inline float32_t GetLongVelocity() const noexcept
    {
        return long_velocity_;
    }
    /**
     * @brief Set longitudial velocity
     *
     * @param[in] long_velocity
     */
    inline void SetLongVelocity(float32_t long_velocity) noexcept
    {
        long_velocity_ = long_velocity;
    }
    /**
     * @brief Get obstacle id
     *
     * @return id_
     */
    inline uint8_t GetId() const noexcept
    {
        return id_;
    }
    /**
     * @brief Set obstacle id
     *
     * @param[in] id
     */
    inline void SetId(uint8_t id) noexcept
    {
        id_ = id;
    }
    /**
     * @brief Check is this obstacle is valid
     *
     * @return true if the obstacle is valid otherwise return false
     */
    inline bool_t IsValid() const noexcept
    {
        return part_a_valid_ && part_b_valid_ && part_c_valid_ && part_d_valid_ && part_e_valid_;
    }
    /**
     * @brief Get part_a_valid
     *
     * @return part_a_valid_
     */
    inline bool_t GetPartAValid() const noexcept
    {
        return part_a_valid_;
    }
    /**
     * @brief Get part_b_valid
     *
     * @return part_b_valid_
     */
    inline bool_t GetPartBValid() const noexcept
    {
        return part_b_valid_;
    }
    /**
     * @brief Get part_c_valid
     *
     * @return part_c_valid_
     */
    inline bool_t GetPartCValid() const noexcept
    {
        return part_c_valid_;
    }
    /**
     * @brief Get part_d_valid
     *
     * @return part_d_valid_
     */
    inline bool_t GetPartDValid() const noexcept
    {
        return part_d_valid_;
    }
    /**
     * @brief Get part_e_valid
     *
     * @return part_e_valid_
     */
    inline bool_t GetPartEValid() const noexcept
    {
        return part_e_valid_;
    }
    /**
     * @brief Set part A of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartAValid(bool_t valid) noexcept
    {
        part_a_valid_ = valid;
    }
    /**
     * @brief Set part B of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartBValid(bool_t valid) noexcept
    {
        part_b_valid_ = valid;
    }
    /**
     * @brief Set part C of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartCValid(bool_t valid) noexcept
    {
        part_c_valid_ = valid;
    }
    /**
     * @brief Set part D of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartDValid(bool_t valid) noexcept
    {
        part_d_valid_ = valid;
    }
    /**
     * @brief Set part E of obstacle is valid
     *
     * @param[in] valid
     */
    inline void SetPartEValid(bool_t valid) noexcept
    {
        part_e_valid_ = valid;
    }

private:
    holo::common::Timestamp timestamp_;

    float32_t long_dist_;                    //! 16|12@1+ (0.0625,0) [0|255.875] "Unit_Meter"
    float32_t angle_center_;                 //! 35|11@1+ (0.00048828125,-0.5) [-0.5|0.4990234375] "Unit_Radia"
    uint8_t   classification_;               //! 56|4@1+ (1,0) [0|15] ""
    float32_t angle_width_;                  //! 23|11@1+ (0.00048828125,0) [0|0.9990234375] "Unit_Radia"
    float32_t confidence_;                   //! 34|7@1+ (0.0078125,0.015625) [0.015625|1] ""
    float32_t angle_speed_;                  //! 47|9@1+ (0.005,-1.25) [-1.25|1.3] "Unit_RadiaPerSecon"
    float32_t angle_overlap_egolane_left_;   //! 42|9@1+ (0.0009765625,-0.25) [-0.25|0.248046875] "Unit_Radia"
    float32_t angle_overlap_egolane_right_;  //! 33|9@1+ (0.0009765625,-0.25) [-0.25|0.248046875] "Unit_Radia"
    float32_t inv_ttc_;                      //! 16|10@1+ (0.015625,-8) [-8|7.96875] "Unit_Hertz"
    uint16_t  age_;                          //! 51|12@1+ (1,0) [0|4094] ""
    float32_t angle_edge_left_;              //! 16|11@1+ (0.00048828125,-0.5) [-0.5|0.49951171875] "Unit_Radia"
    float32_t angle_edge_right_;             //! 27|11@1+ (0.00048828125,-0.5) [-0.5|0.49951171875] "Unit_Radia"
    uint8_t   id_;                           //! 56|8@1+ (1,0) [1|254] ""
    float32_t long_velocity_;                //! 16|11@1+ (0.01388889,-12) [-12|12.00000192] "Unit_MeterPerSecon"
    bool_t    part_a_valid_;                 //! part a valid indicator
    bool_t    part_b_valid_;                 //! part b valid indicator
    bool_t    part_c_valid_;                 //! part c valid indicator
    bool_t    part_d_valid_;                 //! part d valid indicator
    bool_t    part_e_valid_;                 //! part e valid indicator

    static const float32_t      kobj_width_min_;
    static const float32_t      kobj_length_;
    static const float32_t      kobj_height_;
    static const float32_t      kobj_confidence_min_;
    static const Classification kobj_class_remap_table_[16];
};
}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
#endif
