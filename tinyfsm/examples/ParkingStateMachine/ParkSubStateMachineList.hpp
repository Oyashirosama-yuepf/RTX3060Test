#ifndef PARK_SUB_STATE_MACHINE_LIST
#define PARK_SUB_STATE_MACHINE_LIST

#include <tinyfsm.hpp>
#include <iostream>
#include "CommonStruct.hpp"

namespace ParkTinyFsm { 

namespace SubFsmList {

// ----------------------------------------------------------------------------
// 2. State Machine Base Class Declaration
//
template<Type inum>
class ParkSubFsmList : public tinyfsm::Fsm< ParkSubFsmList<inum> >
{
public:
  static void reset(void) {}
  /* default reaction for unhandled events */
  virtual void react(ParkEvent const & park_event) { };
  
  virtual void entry(void) { };  /* entry actions in some states */
  virtual void exit(void)  { };  /* no exit actions */
};

// ----------------------------------------------------------------------------
// 2. State Machine List Declaration
//

using sub_fsm_list = tinyfsm::FsmList<
  ParkSubFsmList<Type::CHECK>,
  ParkSubFsmList<Type::CRUSE>,
  ParkSubFsmList<Type::MAPPING>,
  ParkSubFsmList<Type::PATH_LEARN>
  >;


}   /// namespace SubFsmList
}   /// namespace ParkTinyFsm


#endif   /// PARK_SUB_STATE_MACHINE_LIST
