#include <sstream>
#include <vector>

#include "AnalysisInfo.h"
#include "AnalysisSteering.h"
#include "EventSource.h"
#include "SourceFactory.h"
#include "EventDump.h"
#include "ParticleMass.h"
#include "Event.h"


int main( int argc, char* argv[] ) {

  // store command line parameters
  AnalysisInfo* info = new AnalysisInfo( argc, argv );

  // create data source
  EventSource* es = SourceFactory::create( info );

  // create a list of analyzers
  std::vector<AnalysisSteering*> aList;

  // create object to dump event
  // and store into list of analyzers
  aList.push_back(new EventDump);

  // create object to compute mean and rms energies
  // and store into list of analyzers
  aList.push_back(new ParticleMass);

  // initialize all analyzers
  for (auto as: aList) as->beginJob();

  // loop over events
  const Event* ev;
  while ( ( ev = es->get() ) != nullptr )
  {
    for ( auto as: aList ) as->process( *ev );
    delete ev;
  }

  // finalize all analyzers
  for ( auto as: aList ) as->endJob();

  delete es;

  return 0;

}
