#ifndef FSMLIST_HPP_INCLUDED
#define FSMLIST_HPP_INCLUDED

#include <tinyfsm.hpp>
#include "ParkStateMachine.hpp"
#include "ParkSubStateMachineList.hpp"
#include "iostream"

namespace ParkTinyFsm {

  /** dispatch event to all fsm in fsm list, now there is only ParkFsm" */
  template<typename E>
  void send_event(E const & event) {
    ParkFsm::dispatch<E>(event);
  }

  namespace SubFsmList {

    template<typename E, Type inum>
    void send_event_subfsm(E const & event) {
      ParkSubFsmList<inum>::dispatch(event);
      std::cout << "sub fsm send event " << static_cast<int>(inum) << "..." << std::endl;
    }

  }
}


#endif
