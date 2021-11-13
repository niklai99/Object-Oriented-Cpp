#include "ProperTime.h"
#include "../AnalysisFramework/Event.h"
#include "../AnalysisUtilities/Utilities.h"
#include "../AnalysisUtilities/Constants.h"

#include <cmath>
#include "ParticleReco.h"

// constructor
ProperTime::ProperTime() {
}


// destructor
ProperTime::~ProperTime() {
}


// recompute tag informations for new event
void ProperTime::update( const Event& ev )
{
  static ParticleReco* part_rec = ParticleReco::instance();

  double e = part_rec->part_en();
  double m = part_rec->part_m();
  double x = ev.coord_x();
  double y = ev.coord_y();
  double z = ev.coord_z();
  double p = sqrt(e*e-m*m);
  double d = sqrt(x*x+y*y+z*z);
  double c = Constants::lightVelocity;

  time = d * m / ( p*c );

  return;
}

// return particle type
ProperTime::ParticleType ProperTime::part_type()
{
  // check for new event and return result
  check();
  return type;
}


// return particle energy
double ProperTime::part_en()
{
  // check for new event and return result
  check();
  return energy;
}


// return particle mass
double ProperTime::part_m()
{
  // check for new event and return result
  check();
  return mass;
}

double ProperTime::decayTime(){
  // check for new event and return result
  check();
  return time;
}
