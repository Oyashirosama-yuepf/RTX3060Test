/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hmi_parking_state.h
 * @brief This header file defines hmi parking state
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HMI_PARKING_STATE_H_
#define HOLO_PARKING_BASE_SYSTEM_HMI_PARKING_STATE_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking
{
namespace system
{
/**
 * @brief This class defines hmi parking state
 */
class HmiParkingState
{
public:
    enum class ParkingStateMachineStateType : uint8_t
    {
        POWEROFF                = 0U,
        STANDBY                 = 1U,
        PATH_STUDY              = 2U,
        STUDY_FINISHED          = 3U,
        MAPPING                 = 4U,
        MAPPING_FINISHED        = 5U,
        CHECKING                = 6U,
        CHECKING_FINISHED       = 7U,
        ACTIVE                  = 8U,
        SUSPEND                 = 9U,
        CHECKING_FAILED         = 10U,
        COMPLETED               = 11U,
        TERMINATED              = 12U,
        HPA_FAILURE             = 13U,
        PARKING_SLOT            = 14U,
        RELEASE_AND_DR          = 15U,
        APA_REQUEST             = 16U,
        SEND_SLOT               = 17U,
        RELEASE_SLOT_MANAGER    = 18U,
        APA_ACTIVE              = 19U,
        APA_COMPLETED           = 20U,
        HPA_READY               = 21U,
        MOTOVIS_HPA_READY       = 22U,
        MOTOVIS_STUDY_MAP_READY = 23U,
        WILL_PATH_STUDY         = 24U,
        INTERRUPTION            = 25U,
        HANDSHAKE               = 26U,
        UNHANDSHAKE             = 27U,
    };

    enum class ParkingPathLearningStateType : uint8_t
    {
        STANDBY = 0U,
        ACTIVE  = 1U,
        SUCCESS = 2U,
        FAILED  = 3U,
    };

    enum class ParkingMappingStateType : uint8_t
    {
        STANDBY = 0U,
        ACTIVE  = 1U,
        SUCCESS = 2U,
        FAILED  = 3U,
    };

    enum class ParkingCheckingStateType : uint8_t
    {
        STANDBY = 0U,
        ACTIVE  = 1U,
        SUCCESS = 2U,
        FAILED  = 3U,
    };

    enum class ParkingCruisingStateType : uint8_t
    {
        STANDBY           = 0U,
        ACTIVE            = 1U,
        SUCCESS           = 2U,
        SUSPEND           = 3U,
        OBSTACLE_STOPPING = 4U,
        FAILED            = 5U,
    };

    enum class LearningFailureType : uint8_t
    {
        NORMAL                        = 0U,
        OUT_OF_DISTANCE_RANGE         = 1U,
        OUT_OF_SPEED_RANGE            = 2U,
        OUT_OF_LEARNING_TIME          = 3U,
        UNABLE_TO_SET_START_END_POINT = 4U,
        LEARING_FAILED                = 5U,
        BRAKE_PEDAL_PRESSED           = 6U,
    };

    enum class ParkFailureType : uint8_t
    {
        NORMAL_REVERSIBLE             = 0U,
        MOBILEPHONE_OUT_OF_RANGE      = 1U,
        MOBILEPHONE_BOT_CONNECTED     = 2U,
        PASSENGER_DOOR_OPENED         = 3U,
        OBSTACLE_IN_TRAJECTORY        = 4U,
        SUSPEND_BUTTON_PRESSED        = 5U,
        BRAKE_PEDAL_PRESSED           = 6U,
        NORMAL_IRREVERSIBLE           = 7U,
        CRUISING_OVERTIME             = 8U,
        EXTERNAL_ECU_ACTIVE           = 9U,
        EXTERNAL_ECU_FAILURE          = 10U,
        DOOR_OPENED_WITHOUT_DRIVER    = 11U,
        DRIVER_DOOR_OPENED            = 12U,
        SEATBELT_UNFASTEN_WITH_DRIVER = 13U,
        TERMINATE_BUTTON_PRESSED      = 14U,
    };

    struct ODMExceptionState
    {
        uint8_t camera_state;
        uint8_t obstacle_dis_state;
        uint8_t static_element_proportion_state;
        uint8_t light_state;
        uint8_t weather_state;
        uint8_t slope_state;
        uint8_t turn_radius_state;
    };

    struct CarExceptionState
    {
        uint8_t driver_door_state;
        uint8_t copilot_door_state;
        uint8_t left_rear_door_state;
        uint8_t right_rear_door_state;
        uint8_t bonnet_state;
        uint8_t trunk_state;
        uint8_t l_mirror_state;
        uint8_t r_mirror_state;
        uint8_t driver_safe_belt_state;
        uint8_t brake_state;
        uint8_t epb_state;
        uint8_t gear_state;
        uint8_t crash_state;
        uint8_t phone_state;
    };

    struct DiagExceptionState
    {
        uint8_t diag_state;
        uint8_t pedal_state;
        uint8_t gear_state;
        uint8_t vcu_state;
        uint8_t eps_state;
        uint8_t esp_state;
        uint8_t epb_state;
        uint8_t tbox_state;
        uint8_t charge_state;
    };

    struct MonitorException
    {
        uint8_t monitor_state;
        uint8_t monitor_cause;
    };

    struct AllStateMachineExceptionState
    {
        MonitorException   monitor_exception;
        DiagExceptionState diag_exception;
        ODMExceptionState  odm_exception;
        CarExceptionState  car_exception;
    };

    struct APAStateMachineState
    {
        uint8_t PAS_APAQuitInd_FromAPA;
        uint8_t PAS_APADrvReq_FromAPA;
        uint8_t PAS_APARecInd_FromAPA;
    };

    /**
     * @brief default constructor
     */
    HmiParkingState() noexcept
      : timestamp_()
      , current_state_(ParkingStateMachineStateType::POWEROFF)
      , last_state_(ParkingStateMachineStateType::POWEROFF)
      , previous_state_(ParkingStateMachineStateType::POWEROFF)
      , path_learning_state_(ParkingPathLearningStateType::STANDBY)
      , mapping_state_(ParkingMappingStateType::STANDBY)
      , checking_state_(ParkingCheckingStateType::STANDBY)
      , cruising_state_(ParkingCruisingStateType::STANDBY)
      , learning_failure_(LearningFailureType::NORMAL)
      , park_failure_(ParkFailureType::NORMAL_REVERSIBLE)
      , mapping_progress_(0)
      , diag_exception_{}
      , monitor_exception_(0)
      , car_exception_{}
      , odm_exception_{}
      , take_over_exception_(0U)
      , current_state_timer_(0.0)
    {
        apa_statemachine_state_.PAS_APADrvReq_FromAPA  = 0U;
        apa_statemachine_state_.PAS_APARecInd_FromAPA  = 0U;
        apa_statemachine_state_.PAS_APAQuitInd_FromAPA = 0U;
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

    float GetCurrentStateTimer() const noexcept
    {
        return current_state_timer_;
    }

    void SetCurrentStateTimer(float const current_state_timer)
    {
        current_state_timer_ = current_state_timer;
    }

    uint8_t GetTakeOverException() const noexcept
    {
        return take_over_exception_;
    }

    void SetTakeOverException(uint8_t const take_over_exception)
    {
        take_over_exception_ = take_over_exception;
    }

    void SetAPAStateMachineState(APAStateMachineState const apa_statemachine_state)
    {
        apa_statemachine_state_ = apa_statemachine_state;
    }

    APAStateMachineState GetAPAStateMachineState() const noexcept
    {
        return apa_statemachine_state_;
    }

    uint32_t GetMonitorException() const noexcept
    {
        return monitor_exception_;
    }

    void SetMonitorException(uint32_t const monitor_exception)
    {
        monitor_exception_ = monitor_exception;
    }

    DiagExceptionState GetDiagException() const noexcept
    {
        return diag_exception_;
    }

    void SetDiagException(DiagExceptionState const diag_exception)
    {
        diag_exception_ = diag_exception;
    }

    CarExceptionState GetCarException() const noexcept
    {
        return car_exception_;
    }

    void SetCarException(CarExceptionState const car_exception)
    {
        car_exception_ = car_exception;
    }

    ODMExceptionState GetODMException() const noexcept
    {
        return odm_exception_;
    }

    void SetODMException(ODMExceptionState const odm_exception)
    {
        odm_exception_ = odm_exception;
    }
    /* current_state_ */
    ParkingStateMachineStateType GetCurrentState() const noexcept
    {
        return current_state_;
    }

    void SetCurrentState(ParkingStateMachineStateType const current_state)
    {
        current_state_ = current_state;
    }
    /* previous_state */
    ParkingStateMachineStateType GetPreviousState() const noexcept
    {
        return previous_state_;
    }

    void SetPreviousState(ParkingStateMachineStateType const previous_state)
    {
        previous_state_ = previous_state;
    }

    /* last_state_ */
    ParkingStateMachineStateType GetLastState() const noexcept
    {
        return last_state_;
    }

    void SetLastState(ParkingStateMachineStateType const last_state)
    {
        last_state_ = last_state;
    }

    /* path_learning_state_ */
    ParkingPathLearningStateType GetPathLearningState() const noexcept
    {
        return path_learning_state_;
    }

    void SetPathLearningState(ParkingPathLearningStateType const path_learning_state)
    {
        path_learning_state_ = path_learning_state;
    }

    /* mapping_state_ */
    ParkingMappingStateType GetMappingState() const noexcept
    {
        return mapping_state_;
    }

    void SetMappingState(ParkingMappingStateType const mapping_state)
    {
        mapping_state_ = mapping_state;
    }

    /* checking_state_ */
    ParkingCheckingStateType GetCheckingState() const noexcept
    {
        return checking_state_;
    }

    void SetCheckingState(ParkingCheckingStateType const checking_state)
    {
        checking_state_ = checking_state;
    }

    /* cruising_state_ */
    ParkingCruisingStateType GetCruisingState() const noexcept
    {
        return cruising_state_;
    }

    void SetCruisingState(ParkingCruisingStateType const cruising_state)
    {
        cruising_state_ = cruising_state;
    }

    /* learning_failure_ */
    LearningFailureType GetLearningFailure() const noexcept
    {
        return learning_failure_;
    }

    void SetLearningFailure(LearningFailureType const learning_failure)
    {
        learning_failure_ = learning_failure;
    }

    /* park_failure_ */
    ParkFailureType GetParkFailure() const noexcept
    {
        return park_failure_;
    }

    void SetParkFailure(ParkFailureType const park_failure)
    {
        park_failure_ = park_failure;
    }

    /* mapping_progress_ */
    uint8_t GetMappingProgress() const noexcept
    {
        return mapping_progress_;
    }

    void SetMappingProgress(uint8_t const mapping_progress)
    {
        mapping_progress_ = mapping_progress;
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
                   static_cast<uint8_t>(current_state_), static_cast<uint8_t>(last_state_),
                   static_cast<uint8_t>(path_learning_state_), static_cast<uint8_t>(mapping_state_),
                   static_cast<uint8_t>(checking_state_), static_cast<uint8_t>(cruising_state_),
                   static_cast<uint8_t>(learning_failure_), static_cast<uint8_t>(park_failure_), mapping_progress_);
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
        serializer << timestamp_ << static_cast<uint8_t>(current_state_) << static_cast<uint8_t>(last_state_)
                   << static_cast<uint8_t>(path_learning_state_) << static_cast<uint8_t>(mapping_state_)
                   << static_cast<uint8_t>(checking_state_) << static_cast<uint8_t>(cruising_state_)
                   << static_cast<uint8_t>(learning_failure_) << static_cast<uint8_t>(park_failure_)
                   << mapping_progress_ << holo::serialization::align;
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
        uint8_t current_state, last_state, path_learning_state, mapping_state, checking_state, cruising_state,
            learning_failure, park_failure;
        /* deserialize data */
        deserializer >> timestamp_ >> current_state >> last_state >> path_learning_state >> mapping_state >>
            checking_state >> cruising_state >> learning_failure >> park_failure >> mapping_progress_ >>
            holo::serialization::align;
        current_state_       = static_cast<ParkingStateMachineStateType>(current_state);
        last_state_          = static_cast<ParkingStateMachineStateType>(last_state);
        path_learning_state_ = static_cast<ParkingPathLearningStateType>(path_learning_state);
        mapping_state_       = static_cast<ParkingMappingStateType>(mapping_state);
        checking_state_      = static_cast<ParkingCheckingStateType>(checking_state);
        cruising_state_      = static_cast<ParkingCruisingStateType>(cruising_state);
        learning_failure_    = static_cast<LearningFailureType>(learning_failure);
        park_failure_        = static_cast<ParkFailureType>(park_failure);
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    ParkingStateMachineStateType current_state_;
    ParkingStateMachineStateType last_state_;
    ParkingStateMachineStateType previous_state_;
    ParkingPathLearningStateType path_learning_state_;
    ParkingMappingStateType      mapping_state_;
    ParkingCheckingStateType     checking_state_;
    ParkingCruisingStateType     cruising_state_;
    LearningFailureType          learning_failure_;
    ParkFailureType              park_failure_;
    uint8_t                      mapping_progress_;  // 0 ~ 100
    // AllStateMachineExceptionState all_sm_exception_state_;
    DiagExceptionState   diag_exception_;
    uint32_t             monitor_exception_;
    CarExceptionState    car_exception_;
    ODMExceptionState    odm_exception_;
    uint8_t              take_over_exception_;
    float                current_state_timer_;
    APAStateMachineState apa_statemachine_state_;
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
