#ifndef COMMON_STRUCT_INCLUDE
#define COMMON_STRUCT_INCLUDE

#include <tinyfsm.hpp>
#include "iostream"

namespace ParkTinyFsm {
    struct ParkingInput {};
    struct ConstraintState {};
    struct ParkingStateMachine {};

    enum class ParkingStateMachineStateType : uint8_t {
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

    enum class ParkingSubStateType : uint8_t {
        STANDBY           = 0U,
        ACTIVE            = 1U,
        SUCCESS           = 2U,
        SUSPEND           = 3U,
        OBSTACLE_STOPPING = 4U,
        FAILED            = 5U,
    };

    namespace SubFsmList {
        enum class Type : uint8_t
        {
            CHECK = 0U,
            CRUSE  = 1U,
            MAPPING = 2U,
            PATH_LEARN  = 3U,
        };
    }
    
    struct ParkEvent : tinyfsm::Event {
        ParkingInput park_input;
        ConstraintState constraint_state;
        ParkingStateMachine parking_state_machine;
    };
}

#endif   /// COMMON_STRUCT_INCLUDE