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

#ifndef PARK_FSM_INCLUDE
#define PARK_FSM_INCLUDE

#include <tinyfsm/include/tinyfsm.h>
#include <parking_manager/parking_state_machine/state_machine_structure.h>

namespace ParkTinyFsm {

using ParkingInput = holo::parking_cmw_app::parking_manager::ParkingInput;
// ----------------------------------------------------------------------------
// Event declarationsn 状态转移触发事件注册
struct ParkEvent : tinyfsm::Event {
  ParkingInput parking_input;
};

struct SwitchToPowerOff : ParkEvent {};    // 切换进入关机状态的事件
struct SwitchToStandby : ParkEvent {};     // 切换进入待机状态的事件（Apa未开启）
struct SwitchToSearch : ParkEvent {};      // 切换进入搜索状态的事件（Apa开启）
struct SwitchToApaReady : ParkEvent {};    // 切换进入ApaReady状态的事件（搜索车位成功）
struct SwitchToPark : ParkEvent {};        // 切换进入泊车控制状态的事件（请求控制权成功）
struct SwitchToParkSuccess : ParkEvent {}; // 切换进入泊车成功状态（APA成功）

class ParkFsm
: public tinyfsm::Fsm<ParkFsm>
{
  /* NOTE: react(), entry() and exit() functions need to be accessible
   * from tinyfsm::Fsm class. You might as well declare friendship to
   * tinyfsm::Fsm, and make these functions private:
   *
   * friend class Fsm;
   */
public:

  /* default reaction for unhandled events */
  void react(tinyfsm::Event const &) { 
    LOG(INFO) << "input an unhandled events, please check";
  }

  virtual void react(SwitchToPowerOff const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void react(SwitchToStandby const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void react(SwitchToSearch const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void react(SwitchToApaReady const &) {
    LOG(INFO) << "unregistered event for current state";
  }
  
  virtual void react(SwitchToPark const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void react(SwitchToParkSuccess const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void entry(void) { 
    LOG(INFO) << "unregistered entry react for current state";
  };  /* entry actions in some states */

  virtual void exit(void)  {
    LOG(INFO) << "unregistered exit react for current state";
   };  /* no exit actions at all */
   
};

/** dispatch event to all fsm in fsm list */
template<typename E>
void send_event(E const & event) {
  ParkFsm::dispatch<E>(event);
}

}   /// namespace ParkTinyFsm


#endif   /// PARK_FSM_INCLUDE
