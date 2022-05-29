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

// Single State of ApaStateMachine Statement ----------------------------------------------------
// normal state
class Poweroff;
class Standby;
class Search;
class ApaReady;
class Park;
class ParkSuccess;
// abnormal state
class ParkWarning;
class ParkError;

// Single State of ApaStateMachine --------------------------------------------------------------
// 0. State: Poweroff

class Poweroff : public ParkFsm
{
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
class Standby : public ParkFsm
{
  void entry() override {
    LOG(INFO) << "entry Stand by status";
  }
  void exit() override {
    LOG(INFO) << "exit Stand by Status";
  }

  void react(SwitchToPowerOff const &) override {
    LOG(INFO) << "react for switch to poweroff event";
    transit<Poweroff>();
  }

  void react(SwitchToSearch const &) override {
    LOG(INFO) << "react for switch to study map event";
    transit<Search>();
  }
};

// ----------------------------------------------------------------------------
// 2. State: Search
class Search : public ParkFsm
{
  void entry() override {
    LOG(INFO) << "entry Stand by status";
  }
  void exit() override {
    LOG(INFO) << "exit Stand by Status";
  }

  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to poweroff event";
    transit<Standby>();
  }

  void react(SwitchToApaReady const &) override {
    LOG(INFO) << "react for switch to study map event";
    transit<ApaReady>();
  }
};

// ----------------------------------------------------------------------------
// 3. State: ApaReady
class ApaReady : public ParkFsm
{
  void entry() override {
    LOG(INFO) << "enter study map ready status";
  }
  void exit() override {
    LOG(INFO) << "exit study map ready Status";
  }

  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to hpa ready event";
    transit<Standby>();
  }

  void react(SwitchToSearch const &) override {
    LOG(INFO) << "react for switch to study map event";
    transit<Search>();
  }

  void react(SwitchToPark const &) override {
    LOG(INFO) << "react for switch to standby event";
    transit<Park>();
  }
};

// ----------------------------------------------------------------------------
// 4. State: Park
class Park : public ParkFsm
{
  void entry() override {
    LOG(INFO) << "enter hpa ready status";
  }
  void exit() override {
    LOG(INFO) << "exit hpa ready Status";
  }

  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to standby event";
    transit<Standby>();
  }

  void react(SwitchToParkSuccess const &) override {
    LOG(INFO) << "react for switch to park success";
    transit<ParkSuccess>();
  }
};

// ----------------------------------------------------------------------------
// 5. State: Park Success
class ParkSuccess : public ParkFsm
{
  void entry() override {
    LOG(INFO) << "enter hpa ready status";
  }
  void exit() override {
    LOG(INFO) << "exit hpa ready Status";
  }

  void react(SwitchToStandby const &) override {
    LOG(INFO) << "react for switch to standby event";
    transit<Standby>();
  }
};

}   /// namespace ParkTinyFsm

// ----------------------------------------------------------------------------
// // Initial state definition

#endif  /// PARK_FSM_STATE_INCLUDE