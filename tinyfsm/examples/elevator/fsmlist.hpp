#ifndef FSMLIST_HPP_INCLUDED
#define FSMLIST_HPP_INCLUDED

#include <tinyfsm.hpp>

#include "elevator.hpp"
#include "motor.hpp"
#include "iostream"

using fsm_list = tinyfsm::FsmList<Motor, Elevator>;

/** dispatch event to both "Motor" and "Elevator" */
template<typename E>
void send_event(E const & event)
{
  fsm_list::template dispatch<E>(event);
  std::cout << "send event" << std::endl;
}


#endif
