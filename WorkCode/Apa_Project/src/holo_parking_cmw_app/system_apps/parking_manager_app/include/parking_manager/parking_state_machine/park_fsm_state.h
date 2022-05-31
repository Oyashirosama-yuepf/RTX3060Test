/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file park_state_machine.cpp
 * @brief This cpp file defines hmi converter app class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#ifndef PARK_FSM_STATE_INCLUDE
#define PARK_FSM_STATE_INCLUDE

#include <parking_manager/parking_state_machine/park_fsm.h>

namespace ParkTinyFsm {
    
using ParkingOutput = holo::parking_cmw_app::parking_manager::ParkingOutput;
ParkingOutput GetParkingOutput();

}   /// namespace ParkTinyFsm

// ----------------------------------------------------------------------------
// // Initial state definition

#endif  /// PARK_FSM_STATE_INCLUDE