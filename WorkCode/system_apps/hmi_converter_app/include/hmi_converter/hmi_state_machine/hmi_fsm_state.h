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

#ifndef HMI_FSM_STATE_INCLUDE
#define HMI_FSM_STATE_INCLUDE

#include <hmi_converter/hmi_state_machine/hmi_fsm.h>

namespace HmiTinyFsm {

// Single State of ApaStateMachine Statement ----------------------------------------------------
class Poweroff;
class Standby;
class StartApa;
class StopApa;

// Single State of ApaStateMachine --------------------------------------------------------------
// 0. State: Poweroff

class Poweroff : public HmiFsm {
  void entry() override {
    LOG(INFO) << "entry Poweroff status";
  }
  void exit() override {
    LOG(INFO) << "exit Poweroff Status";
  }
  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to standby";
    transit<Standby>();
  }
};

// ----------------------------------------------------------------------------
// 1. State: Standby
class Standby : public HmiFsm {
  void entry() override {
    LOG(INFO) << "entry Stand by status";
  }
  void exit() override {
    LOG(INFO) << "exit Stand by Status";
  }

  void react(SwitchToPowerOff const &) override {
    LOG(INFO) << "react for switch to poweroff";
    transit<Poweroff>();
  }

  void react(SwitchToStartApa const &) override {
    LOG(INFO) << "react for switch to start apa";
    transit<StartApa>();
  }
};

// ----------------------------------------------------------------------------
// 2. State: StartApa
class StartApa : public HmiFsm {
  void entry() override {
    LOG(INFO) << "entry Stand by status";
  }
  void exit() override {
    LOG(INFO) << "exit Stand by Status";
  }

  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to standby";
    transit<Standby>();
  }

  void react(SwitchToStopApa const &) override {
    LOG(INFO) << "react for switch to stop apa";
    transit<StopApa>();
  }
};

// ----------------------------------------------------------------------------
// 3. State: StopApa
class StopApa : public HmiFsm {
  void entry() override {
    LOG(INFO) << "enter study map ready status";
  }
  void exit() override {
    LOG(INFO) << "exit study map ready Status";
  }

  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to standby";
    transit<Standby>();
  }

  void react(SwitchToStartApa const &) override {
    LOG(INFO) << "react for switch to start apa";
    transit<StartApa>();
  }
};

}  /// namespace HmiTinyFsm



#endif  /// HMI_FSM_STATE_INCLUDE

