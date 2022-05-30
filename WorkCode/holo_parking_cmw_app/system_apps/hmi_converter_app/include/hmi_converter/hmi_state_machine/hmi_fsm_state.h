/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file park_state_machine.h
 * @brief This cpp file defines hmi converter app class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#ifndef HMI_FSM_STATE_INCLUDE
#define HMI_FSM_STATE_INCLUDE

#include <hmi_converter/hmi_state_machine/hmi_fsm.h>

namespace HmiTinyFsm {

using HmiOutput = holo::parking_cmw_app::hmi_converter::HmiOutput;
using HmiCommand = holo::parking::system::HmiCommand;

HmiOutput GetHmiOutputInfo();

}   /// namespace HmiTinyFsm


#endif   /// HMI_FSM_STATE_INCLUDE
