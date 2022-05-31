/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obsatcle.h
 * @brief A class to describe continental ars408/srr308 radar obstacles
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/11
 */

#ifndef HOLO_SENSORS_COMMON_CONTINENTAL_CONTI_RADAR_OBSTACLE_H_
#define HOLO_SENSORS_COMMON_CONTINENTAL_CONTI_RADAR_OBSTACLE_H_

#include <holo/common/coordinate.h>
#include <holo/common/extrinsic.h>
#include <holo/common/timestamp.h>
#include <holo/core/common.h>
#include <holo/core/types.h>
#include <holo/obstacle/obstacle_radar.h>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
using holo::common::Classification;
using holo::obstacle::MotionStatus;

class ContiRadarObstacle
{
public:
    /**
     * @brief Default constructor.
     */
    ContiRadarObstacle()
      : timestamp_()
      , meas_counter_(0)
      , id_(0)
      , classification_(0)
      , dist_long_(0.0f)
      , dist_lat_(0.0f)
      , vrel_long_(0.0f)
      , vrel_lat_(0.0f)
      , arel_long_(0.0f)
      , arel_lat_(0.0f)
      , length_(0.0f)
      , width_(0.0f)
      , angle_(0.0f)
      , rcs_(0.0f)
      , dynprop_(0)
      , prob_of_exist_(0)
      , meas_state_(0)
      , dist_long_rms_(0)
      , dist_lat_rms_(0)
      , vrel_long_rms_(0)
      , vrel_lat_rms_(0)
      , arel_long_rms_(0)
      , arel_lat_rms_(0)
      , angle_rms_(0)
      , part_1_valid_(false)
      , part_2_valid_(false)
      , part_3_valid_(false)
    {
    }
    /**
     * @brief Copy constructor
     *
     * @param other The other ContiRadarObstacle object.
     */
    ContiRadarObstacle(const ContiRadarObstacle& other) noexcept
      : timestamp_(other.timestamp_)
      , meas_counter_(other.meas_counter_)
      , id_(other.id_)
      , classification_(other.classification_)
      , dist_long_(other.dist_long_)
      , dist_lat_(other.dist_lat_)
      , vrel_long_(other.vrel_long_)
      , vrel_lat_(other.vrel_lat_)
      , arel_long_(other.arel_long_)
      , arel_lat_(other.arel_lat_)
      , length_(other.length_)
      , width_(other.width_)
      , angle_(other.angle_)
      , rcs_(other.rcs_)
      , dynprop_(other.dynprop_)
      , prob_of_exist_(other.prob_of_exist_)
      , meas_state_(other.meas_state_)
      , dist_long_rms_(other.dist_long_rms_)
      , dist_lat_rms_(other.dist_lat_rms_)
      , vrel_long_rms_(other.vrel_long_rms_)
      , vrel_lat_rms_(other.vrel_lat_rms_)
      , arel_long_rms_(other.arel_long_rms_)
      , arel_lat_rms_(other.arel_lat_rms_)
      , angle_rms_(other.angle_rms_)
      , part_1_valid_(other.part_1_valid_)
      , part_2_valid_(other.part_2_valid_)
      , part_3_valid_(other.part_3_valid_)
    {
    }
    /**
     * @brief Copy assign operator
     *
     * @param other The other ContiRadarObstacle object.
     *
     * @return Reference to this object.
     */
    ContiRadarObstacle& operator=(const ContiRadarObstacle& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }
        timestamp_      = other.timestamp_;
        meas_counter_   = other.meas_counter_;
        id_             = other.id_;
        classification_ = other.classification_;
        dist_long_      = other.dist_long_;
        dist_lat_       = other.dist_lat_;
        vrel_long_      = other.vrel_long_;
        vrel_lat_       = other.vrel_lat_;
        arel_long_      = other.arel_long_;
        arel_lat_       = other.arel_lat_;
        length_         = other.length_;
        width_          = other.width_;
        angle_          = other.angle_;
        rcs_            = other.rcs_;
        dynprop_        = other.dynprop_;
        prob_of_exist_  = other.prob_of_exist_;
        meas_state_     = other.meas_state_;
        dist_long_rms_  = other.dist_long_rms_;
        dist_lat_rms_   = other.dist_lat_rms_;
        vrel_long_rms_  = other.vrel_long_rms_;
        vrel_lat_rms_   = other.vrel_lat_rms_;
        arel_long_rms_  = other.arel_long_rms_;
        arel_lat_rms_   = other.arel_lat_rms_;
        angle_rms_      = other.angle_rms_;
        part_1_valid_   = other.part_1_valid_;
        part_2_valid_   = other.part_2_valid_;
        part_3_valid_   = other.part_3_valid_;
        return *this;
    }
    /**
     * @brief Convert ContiRadarObstacle to HoloObstacleRadar
     *
     * @param output the HoloObstacleRadar
     */
    void ConvertToHoloObstacle(holo::obstacle::ObstacleRadarT<float32_t>& output) const;
    /**
     * @brief Convert ContiRadarObstacle to HoloObstacleRadar with transform
     *
     * @param input the extrinsic between mpc and target coord
     * @param output the HoloObstacleRadar
     */
    void ConvertToHoloObstacleWithTransform(const holo::common::Extrinsicf&            extrinsic,
                                            holo::obstacle::ObstacleRadarT<float32_t>& output) const;
    /* setters & getters */
    inline void SetTimestamp(const holo::common::Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }
    inline holo::common::Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    inline void SetMeasCounter(uint16_t meas_counter) noexcept
    {
        meas_counter_ = meas_counter;
    }
    inline uint16_t GetMeasCounter() const noexcept
    {
        return meas_counter_;
    }
    inline void SetId(uint8_t id) noexcept
    {
        id_ = id;
    }
    inline uint8_t GetId() const noexcept
    {
        return id_;
    }
    inline void SetClassification(uint8_t classification) noexcept
    {
        classification_ = classification;
    }
    inline uint8_t GetClassification() const noexcept
    {
        return classification_;
    }
    inline void SetDistLong(float32_t dist_long) noexcept
    {
        dist_long_ = dist_long;
    }
    inline float32_t GetDistLong() const noexcept
    {
        return dist_long_;
    }
    inline void SetDistLat(float32_t dist_lat) noexcept
    {
        dist_lat_ = dist_lat;
    }
    inline float32_t GetDistLat() const noexcept
    {
        return dist_lat_;
    }
    inline void SetVrelLong(float32_t vrel_long) noexcept
    {
        vrel_long_ = vrel_long;
    }
    inline float32_t GetVrelLong() const noexcept
    {
        return vrel_long_;
    }
    inline void SetVrelLat(float32_t vrel_lat) noexcept
    {
        vrel_lat_ = vrel_lat;
    }
    inline float32_t GetVrelLat() const noexcept
    {
        return vrel_lat_;
    }
    inline void SetArelLong(float32_t arel_long) noexcept
    {
        arel_long_ = arel_long;
    }
    inline float32_t GetArelLong() const noexcept
    {
        return arel_long_;
    }
    inline void SetArelLat(float32_t arel_lat) noexcept
    {
        arel_lat_ = arel_lat;
    }
    inline float32_t GetArelLat() const noexcept
    {
        return arel_lat_;
    }
    inline void SetLength(float32_t length) noexcept
    {
        length_ = length;
    }
    inline float32_t GetLength() const noexcept
    {
        return length_;
    }
    inline void SetWidth(float32_t width) noexcept
    {
        width_ = width;
    }
    inline float32_t GetWidth() const noexcept
    {
        return width_;
    }
    inline void SetAngle(float32_t angle) noexcept
    {
        angle_ = angle;
    }
    inline float32_t GetAngle() const noexcept
    {
        return angle_;
    }
    inline void SetRcs(float32_t rcs) noexcept
    {
        rcs_ = rcs;
    }
    inline float32_t GetRcs() const noexcept
    {
        return rcs_;
    }
    inline void SetDynprop(uint8_t dynprop) noexcept
    {
        dynprop_ = dynprop;
    }
    inline uint8_t GetDynprop() const noexcept
    {
        return dynprop_;
    }
    inline void SetProbOfExist(uint8_t prob_of_exist) noexcept
    {
        prob_of_exist_ = prob_of_exist;
    }
    inline uint8_t GetProbOfExist() const noexcept
    {
        return prob_of_exist_;
    }
    inline void SetMeasState(uint8_t meas_state) noexcept
    {
        meas_state_ = meas_state;
    }
    inline uint8_t GetMeasState() const noexcept
    {
        return meas_state_;
    }
    inline void SetDistLongRms(uint8_t dist_long_rms) noexcept
    {
        dist_long_rms_ = dist_long_rms;
    }
    inline uint8_t GetDistLongRms() const noexcept
    {
        return dist_long_rms_;
    }
    inline void SetDistLatRms(uint8_t dist_lat_rms) noexcept
    {
        dist_lat_rms_ = dist_lat_rms;
    }
    inline uint8_t GetDistLatRms() const noexcept
    {
        return dist_lat_rms_;
    }
    inline void SetVrelLongRms(uint8_t vrel_long_rms) noexcept
    {
        vrel_long_rms_ = vrel_long_rms;
    }
    inline uint8_t GetVrelLongRms() const noexcept
    {
        return vrel_long_rms_;
    }
    inline void SetVrelLatRms(uint8_t vrel_lat_rms) noexcept
    {
        vrel_lat_rms_ = vrel_lat_rms;
    }
    inline uint8_t GetVrelLatRms() const noexcept
    {
        return vrel_lat_rms_;
    }
    inline void SetArelLongRms(uint8_t arel_long_rms) noexcept
    {
        arel_long_rms_ = arel_long_rms;
    }
    inline uint8_t GetArelLongRms() const noexcept
    {
        return arel_long_rms_;
    }
    inline void SetArelLatRms(uint8_t arel_lat_rms) noexcept
    {
        arel_lat_rms_ = arel_lat_rms;
    }
    inline uint8_t GetArelLatRms() const noexcept
    {
        return arel_lat_rms_;
    }
    inline void SetAngleRms(uint8_t angle_rms) noexcept
    {
        angle_rms_ = angle_rms;
    }
    inline uint8_t GetAngleRms() const noexcept
    {
        return angle_rms_;
    }
    inline void SetPart1Valid(bool_t valid) noexcept
    {
        part_1_valid_ = valid;
    }
    inline bool_t GetPart1Valid() const noexcept
    {
        return part_1_valid_;
    }
    inline void SetPart2Valid(bool_t valid) noexcept
    {
        part_2_valid_ = valid;
    }
    inline bool_t GetPart2Valid() const noexcept
    {
        return part_2_valid_;
    }
    inline void SetPart3Valid(bool_t valid) noexcept
    {
        part_3_valid_ = valid;
    }
    inline bool_t GetPart3Valid() const noexcept
    {
        return part_3_valid_;
    }
    inline bool_t IsValid() const noexcept
    {
        return part_1_valid_ && part_2_valid_ && part_3_valid_;
    }

private:
    holo::common::Timestamp timestamp_;

    uint16_t  meas_counter_;    //! 15|16@0+ (1,0) [0|65535] ""  ExternalUnit
    uint8_t   id_;              //! 7|8@0+ (1,0) [0|255] ""  ExternalUnit
    uint8_t   classification_;  //! 26|3@0+ (1,0) [0|7] ""  ExternalUnit
    float32_t dist_long_;       //! 15|13@0+ (0.2,-500) [-500|1138.2] "m"  ExternalUnit
    float32_t dist_lat_;        //! 18|11@0+ (0.2,-204.6) [-204.6|204.8] "m"  ExternalUnit
    float32_t vrel_long_;       //! 39|10@0+ (0.25,-128) [-128|127.75] "m/s"  ExternalUnit
    float32_t vrel_lat_;        //! 45|9@0+ (0.25,-64) [-64|63.75] "m/s"  ExternalUnit
    float32_t arel_long_;       //! 15|11@0+ (0.01,-10) [-10|10.47] "m/s²"  ExternalUnit
    float32_t arel_lat_;        //! 20|9@0+ (0.01,-2.5) [-2.5|2.61] "m/s²"  ExternalUnit
    float32_t length_;          //! 55|8@0+ (0.2,0) [0|51] "m"  ExternalUnit
    float32_t width_;           //! 63|8@0+ (0.2,0) [0|51] "m"  ExternalUnit
    float32_t angle_;           //! 39|10@0+ (0.4,-180) [-180|229.2] "deg"  ExternalUnit
    float32_t rcs_;             //! 63|8@0+ (0.5,-64) [-64|63.5] "dBm²"  ExternalUnit
    uint8_t   dynprop_;         //! 50|3@0+ (1,0) [0|7] ""  ExternalUnit
    uint8_t   prob_of_exist_;   //! 55|3@0+ (1,0) [0|7] ""  ExternalUnit
    uint8_t   meas_state_;      //! 52|3@0+ (1,0) [0|7] ""  ExternalUnit
    uint8_t   dist_long_rms_;   //! 15|5@0+ (1,0) [0|31] ""  ExternalUnit
    uint8_t   dist_lat_rms_;    //! 10|5@0+ (1,0) [0|31] ""  ExternalUnit
    uint8_t   vrel_long_rms_;   //! 21|5@0+ (1,0) [0|31] ""  ExternalUnit
    uint8_t   vrel_lat_rms_;    //! 16|5@0+ (1,0) [0|31] ""  ExternalUnit
    uint8_t   arel_long_rms_;   //! 27|5@0+ (1,0) [0|31] ""  ExternalUnit
    uint8_t   arel_lat_rms_;    //! 38|5@0+ (1,0) [0|31] ""  ExternalUnit
    uint8_t   angle_rms_;       //! 33|5@0+ (1,0) [0|31] ""  ExternalUnit
    bool_t    part_1_valid_;    //! part a valid indicator
    bool_t    part_2_valid_;    //! part b valid indicator
    bool_t    part_3_valid_;    //! part c valid indicator

    static const Classification kobj_class_remap_table_[8];
    static const float32_t      kobj_confidece_remap_table_[8];
    static const MotionStatus   kobj_motion_status_remap_table_[8];
    static const float32_t      kobj_dvasigma_remap_table_[32];
    static const float32_t      kobj_angsigma_remap_table_[32];
};

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo
#endif
