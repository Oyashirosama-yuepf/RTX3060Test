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

#ifndef HMI_FSM_INCLUDE
#define HMI_FSM_INCLUDE

#include <hmi_converter/hmi_state_machine/state_machine_structure.h>
#include <tinyfsm/include/tinyfsm.h>

namespace HmiTinyFsm {

// ----------------------------------------------------------------------------
// Event declarationsn 状态转移触发事件注册
struct HmiEvent : tinyfsm::Event {

};

struct SwitchToPowerOff : HmiEvent {};    // 切换进入关机状态的事件
struct SwitchToStandby : HmiEvent {};     // 切换进入待机状态的事件（Apa未开启）
struct SwitchToStartApa : HmiEvent {};    // 切换进入Apa开启状态
struct SwitchToStopApa : HmiEvent {};     // 切换进入Apa关闭状态


// ----------------------------------------------------------------------------
// Elevator (FSM base class) declaration
//

class HmiFsm
: public tinyfsm::Fsm<HmiFsm>
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

  virtual void react(SwitchToStartApa const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void react(SwitchToStopApa const &) {
    LOG(INFO) << "unregistered event for current state";
  }

  virtual void entry(void) { 
    LOG(INFO) << "unregistered entry react for current state";
  };  /* entry actions in some states */

  virtual void exit(void)  {
    LOG(INFO) << "unregistered exit react for current state";
   };  /* no exit actions at all */
   
};


/** dispatch event to all fsm in fsm list" */
template<typename E>
void send_event(E const & event) {
  HmiFsm::dispatch<E>(event);
}

}   /// namespace HmiTinyFsm


#endif   /// HMI_FSM_INCLUDE
