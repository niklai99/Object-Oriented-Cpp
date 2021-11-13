#include <cmath>
#include "Event.h"

// compute energy from momentum x,y,z components and invariant mass
double compute_E(double px,double py, double pz, double mass)
{
  double energy_sq = px*px + py*py + pz*pz + mass*mass;
  return sqrt(energy_sq);
}

// compute invariant mass from momentum x,y,z components and energy
double compute_M (double px, double py, double pz, double energy)
{
  double m_sq = energy*energy - px*px - py*py - pz*pz;
  double m = m_sq > 0 ? sqrt(m_sq) : -1;
  return m;
}

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass( const Event& ev ) {

  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* particles = ev.part;

  // variables to loop over particles

  int n_p = ev.n_p;
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
    const part_ptr part = particles[i];

    // update momentum sums
    sum_px += part->p_x;
    sum_py += part->p_y;
    sum_pz += part->p_z;

    // update energy sum for K0
    sum_Ek += compute_E(part->p_x, part->p_y, part->p_z, massPion);

    // update energy sum for Lambda0
    if(part->charge > 0)
    {
      count_pos++;
      sum_El += compute_E(part->p_x, part->p_y, part->p_z, massProton);
    }
    if(part->charge < 0)
    {
      count_neg++;
      sum_El += compute_E(part->p_x,part->p_y, part->p_z, massPion);
    }
  }

  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if( !(count_pos == 1 && count_neg == 1) ) return -1;

  // invariant masses for different decay product mass hypotheses
  double m_k = compute_M(sum_px, sum_py, sum_pz, sum_Ek);
  double m_l = compute_M(sum_px, sum_py, sum_pz, sum_El);

  // compare invariant masses with known values and return the nearest one
  double deltaM_k = std::abs( m_k - massK0 );
  double deltaM_l = std::abs( m_l - massLambda0 );
  if (deltaM_k < deltaM_l) return m_k;
  else return m_l;
  //else return m_l;

}

