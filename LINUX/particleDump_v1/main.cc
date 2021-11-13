#include <fstream>

int read(std::ifstream &f, float &x, float &y, float &z, float *px, float *py,
         float *pz, int *charges);

void dump(int nEv, int nP, float x, float y, float z, float *px, float *py,
          float *pz, int *charges);

int main(int argc, char *argv[]) 
{

  // read file name from the command string
  const char *name = argv[1];

  int nEv, nP;                  // event number and particle number
  float x = 0, y = 0, z = 0;    // event position
  int charges[10];              // particle charges
  float px[10], py[10], pz[10]; // particle momentums

  // open file
  std::ifstream file(name);

  // loop over events
  while (file >> nEv)
  {

    // read data
    nP = read(file, x, y, z, px, py, pz, charges);

    // print data
    dump(nEv, nP, x, y, z, px, py, pz, charges);
  }

  return 0;
}
