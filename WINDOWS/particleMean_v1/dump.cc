/* Function to print events read from particle_events.txt */
#include <iostream>
#include "Event.h"

void dump(const Event& ev)
{

  // print event data
  std::cout << ev.n_ev << '\n'
            << ev.x << ' ' << ev.y << ' ' << ev.z << '\n'
            << ev.n_p << std::endl;

  // loop over particles
  int i = 0;
  for (i = 0; i < ev.n_p; i++)
  {
    std::cout << ev.part[i]->charge << ' '
              << ev.part[i]->p_x << ' ' << ev.part[i]->p_y << ' '
              << ev.part[i]->p_z << std::endl;
  }

}
