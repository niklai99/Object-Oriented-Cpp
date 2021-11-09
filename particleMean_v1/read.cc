/* function to read data from particle_events.txt */

#include <fstream>
#include "Event.h"

Event* read(std::ifstream& file)
{

	// variables to store data
	Event *ev;
	int n_ev=0,n_p=0;

	if( !(file >> n_ev) ) return nullptr;

	// store event data
	ev=new Event;
	ev->n_ev = n_ev;
	file >> ev->x >> ev->y >> ev->z >> n_p;
	ev->n_p = n_p;

	// loop over particles and read momentums
	int i=0;
	ev->part = new Particle*[n_p] ;
	for(i=0; i < n_p; i++)
	{
		ev->part[i] = new Particle;
		file >> ev->part[i]->charge >> ev->part[i]->p_x >> ev->part[i]->p_y
			 >> ev->part[i]->p_z;
	}

	return ev;

}
