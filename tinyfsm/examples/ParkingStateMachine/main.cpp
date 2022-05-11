#include "fsmlist.hpp"
#include <iostream>

int main()
{

  using namespace ParkTinyFsm;

  ParkEvent park_event;

  ParkFsm::start();
  SubFsmList::sub_fsm_list::start();

  while(1)
  {
    char c;
    std::cout << "p=poweroff, s=standby, h=hpa_ready, m=study_map_ready ? ";
    std::cin >> c;
    send_event(park_event);
  };
}

