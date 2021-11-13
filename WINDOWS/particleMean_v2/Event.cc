#include "Event.h"

Event::Event( int n, float x, float y, float z ):
 // initializations
  n_ev(n),
  x(x),
  y(y),
  z(z)
{
  // allocate a buffer for particle pointers
  n_p=0;
  part = new Particle*[n_max];
}


Event::~Event()
{
  // delete all the particle pointers
  unsigned int i=0;
  for( i=0; i < n_p; i++ )
    delete part[i];
  // delete the pointers array
  delete[] part;
}


void Event::add( int charge, float px, float py, float pz )
{

  // check for the number of particles, if maximum reached do nothing
  // and return
  if(n_p == n_max) return;

  // create the new particle and fill with data
  Particle* p_new = new Particle{charge, px, py, pz};

  // store the new particle pointer in the array and increase counter
  part[n_p] = p_new;
  n_p++;


  return;

}


// get event id.
int Event::eventNumber() const
{
  return n_ev;
}


// get decay point coordinates
float Event::coord_x() const
{
  return x;
}

float Event::coord_y() const
{
  return y;
}

float Event::coord_z() const
{
  return z;
}


// get number of particles
int Event::nParticles() const
{
  return n_p;
}

// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  if(i < n_p) return part[i];
  else return nullptr;
}

