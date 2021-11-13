#include "ParticleReco.h"
#include "../AnalysisFramework/Event.h"
#include "../AnalysisUtilities/Utilities.h"
#include "../AnalysisUtilities/Constants.h"
#include <iostream>
#include <cmath>

using namespace std;


// constructor
ParticleReco::ParticleReco() {
}


// destructor
ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
    // retrieve particles in the event
  typedef const Event::Particle* part_ptr;

  // variables to loop over particles
  int n_p = ev.nParticles();
  // positive / negative track counters
  int count_pos=0;
  int count_neg=0;

  // variables for momentum sums
  double sum_px=0;
  double sum_py=0;
  double sum_pz=0;

  // variables for energy sums, for K0 and Lambda0
  double sum_Ek=0;
  double sum_El=0;

  // loop over particles - momenta
  int i=0;
  for (i=0; i < n_p; i++)
  {
    // get particle pointer
    const part_ptr part = ev.particle(i);

    // update momentum sums
    sum_px += part->p_x;
    sum_py += part->p_y;
    sum_pz += part->p_z;

    // update energy sum for K0
    sum_Ek += Utilities::compute_E(part->p_x, part->p_y, part->p_z,
                                   Constants::massPion);

    // update energy sum for Lambda0
    if(part->charge > 0)
    {
      count_pos++;
      sum_El += Utilities::compute_E(part->p_x, part->p_y, part->p_z,
                                     Constants::massProton);
    }
    if(part->charge < 0)
    {
      count_neg++;
      sum_El += Utilities::compute_E(part->p_x,part->p_y, part->p_z,
                                     Constants::massPion);
    }
  }

  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if( !(count_pos == 1 && count_neg == 1) ) return;

  // invariant masses for different decay product mass hypotheses
  double m_k = Utilities::compute_M(sum_px, sum_py, sum_pz, sum_Ek);
  double m_l = Utilities::compute_M(sum_px, sum_py, sum_pz, sum_El);


  // compare invariant masses with known values and set final values
  double deltaM_k = std::abs( m_k - Constants::massK0 );
  double deltaM_l = std::abs( m_l - Constants::massLambda0 );

  // ( type, energy and mass )
  if (deltaM_k < deltaM_l)
  {
     type = K0;
     mass = m_k;
     energy = sum_Ek;

  }
  else
  {
    type = Lambda0;
    mass = m_l;
    energy = sum_El;
  }

  return;

}

// return particle type
ParticleReco::ParticleType ParticleReco::part_type()
{
  // check for new event and return result
  check();
  return type;
}


// return particle energy
double ParticleReco::part_en()
{
  // check for new event and return result
  check();
  return energy;
}


// return particle mass
double ParticleReco::part_m()
{
  // check for new event and return result
  check();
  return mass;
}
