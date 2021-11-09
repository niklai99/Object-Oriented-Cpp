#include "Utilities.h"
#include <cmath>

// compute energy from momentum x,y,z components and invariant mass
double Utilities::compute_E(double px,double py, double pz, double mass)
{
  double energy_sq = px*px + py*py + pz*pz + mass*mass;
  return sqrt(energy_sq);
}

// compute invariant mass from momentum x,y,z components and energy
double Utilities::compute_M (double px, double py, double pz, double energy)
{
  double m_sq = energy*energy - px*px - py*py - pz*pz;
  double m = m_sq > 0 ? sqrt(m_sq) : -1;
  return m;
}
