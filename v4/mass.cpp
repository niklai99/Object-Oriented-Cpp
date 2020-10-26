#include <cmath>
#include<iostream>

#include "Event.h"


// compute energy from momentum x,y,z components and invariant mass
double energy(float px, float py, float pz, float M) {

    double e;

    e = sqrt(pow(px, 2) + pow(py, 2) + pow(pz, 2) + pow(M, 2));
  
    return e;
} 

// compute invariant mass from momentum x,y,z components and energy
double inv_mass(float px, float py, float pz, float e) {

    double M;

    M = sqrt(pow(e, 2) - (pow(px, 2) + pow(py, 2) + pow(pz, 2)));
    
    return M;
} 

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

double mass(const Event* ev) {

  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* p = ev -> particle;

  // variables to loop over particles
  int i;

  // positive / negative track counters  
  int negative = 0;
  int positive = 0;

  // variables for momentum sums
  double sum_px = 0;
  double sum_py = 0;
  double sum_pz = 0;
  
  // variables for energy sums, for K0 and Lambda0
  double sum_E_K0 = 0;
  double sum_E_L0 = 0;

  // variables for invariant masses, for K0 and Lambda0
  double m_K0 = 0;
  double m_L0 = 0;

  double diff_K0;
  double diff_L0;

  // loop over particles - momenta
  for (i = 0; i < ev->n_particles; ++i) {
    // get particle pointer
    //??
    // update momentum sums
    sum_px += p[i]->px;
    sum_py += p[i]->py;
    sum_pz += p[i]->pz;
    // update energy sums, for K0 and Lambda0 hypotheses:
    // pion mass for K0,
    // proton or pion mass for Lambda0,
    // for positive or negative particles respectively 
    if (p[i]->q == 1) {
      sum_E_K0 += energy(p[i]->px, p[i]->py, p[i]->pz, massPion);
      sum_E_L0 += energy(p[i]->px, p[i]->py, p[i]->pz, massProton);
      positive++;
      }
    else if (p[i]->q == -1) {
      sum_E_K0 += energy(p[i]->px, p[i]->py, p[i]->pz, massPion);
      sum_E_L0 += energy(p[i]->px, p[i]->py, p[i]->pz, massPion);
      negative++;
      }
    else if (p[i]->q != 1 || p[i]->q != -1 ) return -1;
  }
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if (positive != 1 || negative != 1) return -1;

  // invariant masses for different decay product mass hypotheses
  m_K0 = inv_mass(sum_px, sum_py, sum_pz, sum_E_K0);
  m_L0 = inv_mass(sum_px, sum_py, sum_pz, sum_E_L0);

  // compare invariant masses with known values and return the nearest one

  diff_K0 = fabs(m_K0 - massK0);
  diff_L0 = fabs(m_L0 - massLambda0);

  if(diff_K0 < diff_L0){
    
    //std::cout << "m_K0 = " << m_K0 << std::endl;
    return m_K0;
    
    }
  return -1;
}

