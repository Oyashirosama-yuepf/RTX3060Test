
#include "ParkSubStateMachineList.hpp"

namespace ParkTinyFsm {

namespace SubFsmList {

static void DumpState(ParkingSubStateType inum, const char * state) {
  std::cout << "* Switch[" << static_cast<int>(inum) << "] is " << state << std::endl;
}

// ----------------------------------------------------------------------------
// 1. State Declarations
//

// SubFsm Check Single State
template<ParkingSubStateType sub_fsm_num, Type inum>
class Single_SubState : public ParkSubFsmList<inum>
{
  void entry() override {
    DumpState(sub_fsm_num, "Single_State");
  };

  void react(ParkEvent const & park_event) override {
    std::cout << "sub fsm switch to event:" << std::endl;
    switch (sub_fsm_num) {
      case ParkingSubStateType::STANDBY:
        transit<Single_SubState<ParkingSubStateType::ACTIVE>>();
        std::cout << "sub fsm Check transit Standby" << std::endl;
        break;
      case ParkingSubStateType::ACTIVE:
        transit<Single_SubState<ParkingSubStateType::SUCCESS>>();
        std::cout << "sub fsm Check transit Active" << std::endl;
        break;
      case ParkingSubStateType::SUCCESS:
        transit<Single_SubState<ParkingSubStateType::FAILED>>();
        std::cout << "sub fsm Check transit Success" << std::endl;
        break;
      case ParkingSubStateType::FAILED:
        transit<Single_SubState<ParkingSubStateType::STANDBY>>();
        std::cout << "sub fsm Check transit Failed" << std::endl;
        break;
      default:
        std::cout << "Unregistered info" << std::endl;
        break;
    }
  }
};

}
}

using namespace ParkTinyFsm;
using namespace ParkTinyFsm::SubFsmList;
FSM_INITIAL_STATE(ParkSubFsmList<Type::CHECK>, Single_SubState<ParkingSubStateType::STANDBY, Type::CHECK>)
FSM_INITIAL_STATE(ParkSubFsmList<Type::CRUSE>, Single_SubState<ParkingSubStateType::STANDBY, Type::CRUSE>)
FSM_INITIAL_STATE(ParkSubFsmList<Type::MAPPING>, Single_SubState<ParkingSubStateType::STANDBY, Type::MAPPING>)
FSM_INITIAL_STATE(ParkSubFsmList<Type::PATH_LEARN>, Single_SubState<ParkingSubStateType::STANDBY, Type::PATH_LEARN>)
