#include <fstream>
#include <cmath>
#include <iostream>
#include "Event.h"

Event* read(std::ifstream &f);

void dump(const Event& ev);

void clear(const Event* ev);

bool add(const Event& ev, double m_min, double m_max,
         double& sum_m, double& sum_msq);

int main(int argc, char *argv[])
{
  int n_accepted=0; // number of accepted events
  double sum_m=0; // sum of invariant masses
  double sum_msq=0; // sum of squares of invariant masses
  double mean_m=0; // mean invariant mass
  double rms=0; // rms invariant mass

  // read file name from the command string
  const char *name = argv[1];

  // open file
  std::ifstream file(name);

  // loop over events
  Event* ev;
  while ( (ev=read(file)) != nullptr)
  {
    if(add(*ev, 0.490,0.505, sum_m, sum_msq)) n_accepted++;
    clear(ev);
  }

  // compute mean
  mean_m = sum_m *1./ n_accepted;

  // compute rms
  double ms = sum_msq *1./ n_accepted - mean_m*mean_m;
  ms > 0? rms=sqrt(ms) : rms=0;

  mean_m += 0.490;

  std::cout << "mean\t" << mean_m <<  "\n" << "rms\t" << rms << std::endl;

  return 0;
}
