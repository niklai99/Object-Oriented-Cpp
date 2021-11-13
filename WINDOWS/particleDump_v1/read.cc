/* function to read data from particle_events.txt */

#include <fstream>

int read(std::ifstream& f,float& x,float& y, float& z, 
		float* px, float* py, float* pz, int* charges)
{
	
	// read decay coordinates
	f >> x >> y >> z;

	// read number of particles
	int np = 0;
	f >> np;

	// loop over particles and read momentums
	int i = 0;
	for(i=0; i < np; i++)
		f >> charges[i] >> px[i] >> py[i] >> pz[i];

	// return number of particles
	return np;
}
