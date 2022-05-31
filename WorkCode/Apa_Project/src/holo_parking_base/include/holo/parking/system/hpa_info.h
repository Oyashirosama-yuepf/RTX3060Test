/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_info.h
 * @brief This header file defines hpa info
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HPA_INFO_H_
#define HOLO_PARKING_BASE_SYSTEM_HPA_INFO_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines hpa info
 */
class HpaInfo
{
public:
    enum class ParkStateType : uint8_t
    {
        INACTIVE   = 0U,
        ACTIVE     = 1U,
        COMPLETED  = 2U,
        SUSPEND    = 3U,
        TERMINATED = 4U,
        RECORVERED = 5U,
        FAILED     = 6U,
    };

    enum class LearningFailureType : uint8_t
    {
        NORMAL                         = 0U,
        OUT_OF_DISTANCE_RANGE          = 1U,
        OUT_OF_SPEED_RANGE             = 2U,
        OUT_OF_LEARNING_TIME_ON_LINE   = 3U,
        UNABLE_TO_SET_START_END_POINT  = 4U,
        LEARING_FAILED                 = 5U,
        OUT_OF_LEARNING_TIME_OFF_LINE  = 6U,
        STATIC_OBSTACLES_ARE_TOO_CLOSE = 7U,
        ABNORMAL_LIGHTING              = 8U,
        ABNORMAL_SLOPE                 = 9U,
        ABNORMAL_WEATHER_RAINY_DAY     = 10U,
        SPARSE_ENVIRONMENTAL_FEATURES  = 11U,
        TURNING_RADIUS_EXCEEDED        = 12U,
        DIRTY_FRONT_CAMERA             = 13U,
        HOOD_OPEN                      = 14U,
        ABNORMAL_WEATHER_SNOW_DAY      = 15U,
        FAILED_TO_SAVE_ROUTE           = 16U,
        SET_START_POINT_SPEED_NOT_ZERO = 17U,
        CAR_DOORS_OPEN                 = 18U,
        SEATBELT_UNFASTEN_WITH_DRIVER  = 19U,
        TAILGATE_OPEN                  = 20U,
        OVER_SPEED_WARNING             = 21U,
        OVER_LENGTH_WARNING_L1         = 22U,
        OVER_LENGTH_WARNING_L2         = 23U,

        OVER_TIME_WARINING     = 100U,
        LEARNING_STOP_OVERTIME = 101U,
        BRAKE_PEDAL_PRESSED    = 106U,

        UNKNOWN = 255U,
    };

    enum class ParkFailureType : uint8_t
    {
        // recoverable failure
        NORMAL                         = 0U,
        MOBILEPHONE_OUT_OF_RANGE       = 1U,
        MOBILEPHONE_NOT_CONNECTED      = 2U,
        PASSENGER_DOOR_OPENED          = 3U,
        OBSTACLE_IN_TRAJECTORY         = 4U,
        SUSPEND_BUTTON_PRESSED         = 5U,
        BRAKE_PEDAL_PRESSED            = 6U,
        TAILGATE_OPEN                  = 7U,
        DRIVER_DOOR_OPENED             = 12U,
        SEATBELT_UNFASTEN_WITH_DRIVER  = 13U,
        REARVIEW_MIRROR_FOLDING        = 19U,
        DIRTY_FRONT_CAMERA             = 20U,
        DIRTY_SURROUND_VIEW_CAMERA     = 21U,
        OBSTACLE_IN_TRAJECTORY_HOLD_ON = 28U,

        // unrecoverable failure
        PAUSE_OVERTIME             = 8U,
        EXTERNAL_ECU_ACTIVE        = 9U,
        EXTERNAL_ECU_FAILURE       = 10U,
        DOOR_OPENED_WITHOUT_DRIVER = 11U,
        TERMINATE_BUTTON_PRESSED   = 14U,
        STEERING_WHEEL_TAKEOVER    = 15U,
        GEAR_INTERRUPT             = 16U,
        EPB_APPLY                  = 17U,
        PATH_MATCH_FAILED          = 18U,
        ENGINE_COVER_OPEN          = 22U,
        COLLISION_DETECTION        = 23U,
        HPA_SYSTEM_FAILURE         = 24U,
        ACCELERATOR_TAKEOVER       = 25U,
        CRUISING_OVERTIME          = 26U,
        VEHICLE_BLOCK              = 27U,
        LIGHT_ABNORMAL             = 29U,
        SLOPE_ABNORMAL             = 30U,
        RAINY_DAY                  = 31U,
        FEW_POINT_FEATURE          = 32U,
        SNOWY_DAY                  = 33U,

        UNKNOWN = 255U,
    };

    enum class LocationStateType : uint8_t
    {
        STANDBY = 0U,
        ACTIVE  = 1U,
        SUCCESS = 2U,
        FAILED  = 3U,
    };

    struct HpaParkState
    {
        ParkStateType       park_state;
        LearningFailureType learning_failure;
        ParkFailureType     park_failure;
        uint16_t dynamic_distance;  // distance since start point in Path_Learning or distance to end point in Cruising
        LocationStateType location_state;
    };

    /**
     * @brief default constructor
     */
    HpaInfo() noexcept : timestamp_(), hpa_park_state_{}, is_selectline_(0)
    {
    }

    /* timestamp_ */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /* is_selectline_ */
    uint8_t GetIsSelectline() const noexcept
    {
        return is_selectline_;
    }

    void SetIsSelectline(uint8_t const is_selectline)
    {
        is_selectline_ = is_selectline;
    }

    /* hpa_park_state_ */
    HpaParkState GetHpaParkState() const noexcept
    {
        return hpa_park_state_;
    }

    void SetParkState(HpaParkState const hpa_park_state)
    {
        hpa_park_state_ = hpa_park_state;
    }

    /* park_state */
    ParkStateType GetParkState() const noexcept
    {
        return hpa_park_state_.park_state;
    }

    void SetParkState(ParkStateType const park_state)
    {
        hpa_park_state_.park_state = park_state;
    }

    /* park_failure */
    ParkFailureType GetParkFailure() const noexcept
    {
        return hpa_park_state_.park_failure;
    }

    void SetParkFailure(ParkFailureType const park_failure)
    {
        hpa_park_state_.park_failure = park_failure;
    }

    /* learning_failure */
    LearningFailureType GetLearningFailure() const noexcept
    {
        return hpa_park_state_.learning_failure;
    }

    void SetLearningFailure(LearningFailureType const learning_failure)
    {
        hpa_park_state_.learning_failure = learning_failure;
    }

    /* dynamic_distance */
    uint16_t GetDynamicDistance() const noexcept
    {
        return hpa_park_state_.dynamic_distance;
    }

    void SetDynamicDistance(uint16_t const dynamic_distance)
    {
        hpa_park_state_.dynamic_distance = dynamic_distance;
    }

    /* location_state */
    LocationStateType GetLocationState() const noexcept
    {
        return hpa_park_state_.location_state;
    }

    void SetLocationState(LocationStateType const location_state)
    {
        hpa_park_state_.location_state = location_state;
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
                   static_cast<uint8_t>(hpa_park_state_.park_state), static_cast<uint8_t>(hpa_park_state_.park_failure),
                   static_cast<uint8_t>(hpa_park_state_.learning_failure), hpa_park_state_.dynamic_distance,
                   static_cast<uint8_t>(hpa_park_state_.location_state), is_selectline_);
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
        serializer << timestamp_ << static_cast<uint8_t>(hpa_park_state_.park_state)
                   << static_cast<uint8_t>(hpa_park_state_.park_failure)
                   << static_cast<uint8_t>(hpa_park_state_.learning_failure) << hpa_park_state_.dynamic_distance
                   << static_cast<uint8_t>(hpa_park_state_.location_state) << is_selectline_
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
        uint8_t park_state;
        uint8_t park_failure;
        uint8_t learning_failure;
        uint8_t location_state;
        /* deserialize data */
        deserializer >> timestamp_ >> park_state >> park_failure >> learning_failure >>
            hpa_park_state_.dynamic_distance >> location_state >> is_selectline_ >> holo::serialization::align;
        hpa_park_state_.park_state       = static_cast<ParkStateType>(park_state);
        hpa_park_state_.park_failure     = static_cast<ParkFailureType>(park_failure);
        hpa_park_state_.learning_failure = static_cast<LearningFailureType>(learning_failure);
        hpa_park_state_.location_state   = static_cast<LocationStateType>(location_state);
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    HpaParkState hpa_park_state_;
    uint8_t      is_selectline_;  // 0: not selected; 1: selected
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
