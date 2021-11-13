#include <sstream>
#include <vector>

#include "AnalysisInfo.h"
#include "AnalysisSteering.h"
#include "AnalysisFactory.h"
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
  std::vector<AnalysisSteering*> aList = AnalysisFactory::create( info );

  // initialize all analyzers
  for (auto as: aList) as->beginJob();

  // loop over events
  es->run();

  // finalize all analyzers
  for ( auto as: aList ) as->endJob();

  delete es;

  return 0;

}
