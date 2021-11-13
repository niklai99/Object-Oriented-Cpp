#include "EventDump.h"
#include "../AnalysisFramework/Event.h"
#include "../AnalysisFramework/AnalysisFactory.h"

#include <iostream>


// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
  // create an EventDump when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new EventDump( info );
  }
};
// create a global EventDumpFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;


EventDump::EventDump( const AnalysisInfo* info ):
  AnalysisSteering( info )
{}


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
void EventDump::update( const Event& ev ) {

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
