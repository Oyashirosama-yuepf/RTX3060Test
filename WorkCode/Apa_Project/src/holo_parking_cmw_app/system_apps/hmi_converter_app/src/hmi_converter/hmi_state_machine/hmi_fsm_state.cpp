/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_fsm_state.cpp
 * @brief This cpp file defines hmi converter app class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#include <hmi_converter/hmi_state_machine/hmi_fsm_state.h>

namespace HmiTinyFsm {

// Single State of ApaStateMachine Statement ----------------------------------------------------
class Poweroff;
class Standby;
class StartApa;
class StopApa;


HmiOutput hmi_output_;
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
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::NO_COMMAND));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_UNDEFINED));
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
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::NO_COMMAND));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_UNDEFINED)); 
    transit<Poweroff>();
  }

  void react(SwitchToStartApa const &) override {
    LOG(INFO) << "react for switch to start apa";
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::ENABLE_APA));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_APA)); 
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
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::NO_COMMAND));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_UNDEFINED)); 
    transit<Standby>();
  }

  void react(SwitchToStopApa const &) override {
    LOG(INFO) << "react for switch to stop apa";
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::NO_COMMAND));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_APA)); 
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
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::NO_COMMAND));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_UNDEFINED)); 
    transit<Standby>();
  }

  void react(SwitchToStartApa const &) override {
    LOG(INFO) << "react for switch to start apa";
    hmi_output_.hmi_command_.SetHmiCommand(static_cast<uint8_t>(HmiCommand::HmiCommandType::ENABLE_APA));
    hmi_output_.hmi_command_.SetHmiParkType(static_cast<uint8_t>(HmiCommand::HmiParkType::PARK_TYPE_APA)); 
    transit<StartApa>();
  }
};

HmiOutput GetHmiOutputInfo() {
    return hmi_output_;
}

}  /// namespace HmiTinyFsm

FSM_INITIAL_STATE(HmiTinyFsm::HmiFsm, HmiTinyFsm::StartApa)



