#ifndef PARK_STATE_MACHINE_INCLUDE
#define PARK_STATE_MACHINE_INCLUDE

#include "CommonStruct.hpp"


namespace ParkTinyFsm {

// ----------------------------------------------------------------------------
// Elevator (FSM base class) declaration
//
//template<int status_num>
class ParkFsm
: public tinyfsm::Fsm<ParkFsm>
{
private:
  int ParkFsmNum;
public:
  //ParkFsm():ParkFsmNum(static_cast<int>(status_num)) {};
  /* default reaction for unhandled events */
  void react(tinyfsm::Event const &) { 
    std::cout << "input an unhandled events, please check" << std::endl;
  };

  virtual void react(ParkEvent const & park_event);

  virtual void entry(void) { };  /* entry actions in some states */
  virtual void exit(void)  { };  /* no exit actions at all */
};

}   /// namespace ParkTinyFsm


#endif   /// PARK_STATE_MACHINE_INCLUDE
