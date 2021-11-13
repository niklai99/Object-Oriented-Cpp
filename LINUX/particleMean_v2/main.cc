#include <iostream>
#include <fstream>
#include "Event.h"
#include "MassMean.h"


Event* read(std::ifstream &f);

void dump(const Event& ev);


int main( int argc, char* argv[] ) {

  // open input file
  const char *name = argv[1];
  std::ifstream file(name);

  // create MassMean objects
  MassMean K0(0.495, 0.500);
  MassMean Lambda0(1.115, 1.116);


  // loop over events
  const Event* ev;
  while ( (ev=read(file)) != nullptr)
  {
      K0.add(*ev);
      Lambda0.add(*ev);
      delete ev;
  }

  // compute results
  K0.compute();
  Lambda0.compute();


  // print number of selected events and results for both particles
  std::cout << "K0:\t mean\t" << K0.mMean() <<  "\t" << "rms\t" << K0.mRMS() << '\n'
            << "L0:\t mean\t" << Lambda0.mMean() <<  "\t" << "rms\t" << Lambda0.mRMS() << '\n';

  return 0;

}

