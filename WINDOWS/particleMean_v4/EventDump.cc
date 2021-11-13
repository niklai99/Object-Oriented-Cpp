#include "EventDump.h"
#include "Event.h"
#include <iostream>

using namespace std;

EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::process( const Event& ev ) {

  // print event data
  int n_p = ev.nParticles();
  std::cout << ev.eventNumber() << '\n'
            << ev.coord_x() << ' ' << ev.coord_y() << ' ' << ev.coord_z() << '\n'
            << n_p << std::endl;

  // loop over particles
  int i = 0;
  for (i = 0; i < n_p; i++)
  {
    const Event::Particle* p = ev.particle(i);
    std::cout << p->charge << ' '
              << p->p_x << ' ' << p->p_y << ' ' << p->p_z << std::endl;
  }

  return;
}
