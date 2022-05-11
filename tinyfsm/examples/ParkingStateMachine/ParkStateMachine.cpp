#include <tinyfsm.hpp>

#include "fsmlist.hpp"

namespace ParkTinyFsm {

// ----------------------------------------------------------------------------
// Single_State
//

template<ParkingStateMachineStateType fsm_num>
class Single_State : public ParkFsm
{
  void entry() override {
    std::cout << "entry status:"<< static_cast<int>(fsm_num) << std::endl;
  }
  void exit() override {
    std::cout << "exit Status" << static_cast<int>(fsm_num) << std::endl;
  }
  void react(ParkEvent const & park_event) override {
    std::cout << "switch to event:" << std::endl;
    switch (fsm_num) {
      case ParkingStateMachineStateType::POWEROFF:
        transit<Single_State<ParkingStateMachineStateType::STANDBY>>();
        ParkTinyFsm::SubFsmList::send_event_subfsm<ParkEvent, SubFsmList::Type::CHECK>(park_event);
        std::cout << "transit Poweroff" << std::endl;
        break;
      case ParkingStateMachineStateType::STANDBY:
        transit<Single_State<ParkingStateMachineStateType::PATH_STUDY>>();
        ParkTinyFsm::SubFsmList::send_event_subfsm<ParkEvent, SubFsmList::Type::CRUSE>(park_event);
        std::cout << "transit Standby" << std::endl;
        break;
      case ParkingStateMachineStateType::PATH_STUDY:
        transit<Single_State<ParkingStateMachineStateType::STUDY_FINISHED>>();
        ParkTinyFsm::SubFsmList::send_event_subfsm<ParkEvent, SubFsmList::Type::PATH_LEARN>(park_event);
        std::cout << "transit Path Study" << std::endl;
        break;
      case ParkingStateMachineStateType::STUDY_FINISHED:
        transit<Single_State<ParkingStateMachineStateType::POWEROFF>>();
        ParkTinyFsm::SubFsmList::send_event_subfsm<ParkEvent, SubFsmList::Type::MAPPING>(park_event);
        std::cout << "transit Study Finished" << std::endl;
        break;
      default:
        std::cout << "Unregistered info" << std::endl;
        break;
    }
  }
};

// ----------------------------------------------------------------------------
// Base state: default implementations
//
void ParkFsm::react(ParkEvent const &) {
  std::cout << "default react for switch to power off event" << std::endl;
}

}   /// namespace ParkTinyFsm

// ----------------------------------------------------------------------------
// Initial state definition
//

using namespace ParkTinyFsm;
FSM_INITIAL_STATE(ParkFsm, Single_State<ParkingStateMachineStateType::POWEROFF>)

