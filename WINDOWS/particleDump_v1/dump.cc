/* Function to print events read from particle_events.txt */
#include <iostream>

void dump(int nEv, int nP, float x, float y, float z, float *px, float *py,
          float *pz, int *charges)
{

  // print event data
  std::cout << nEv << std::endl
            << x << ' ' << y << ' ' << z << std::endl
            << nP << std::endl;

  // loop over particles
  int i = 0;
  for (i = 0; i < nP; i++)
    std::cout << charges[i] << ' ' << px[i] << ' ' << py[i] << ' ' << pz[i]
              << std::endl;
}
