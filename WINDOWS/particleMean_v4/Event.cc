#include "Event.h"

Event::Event( int n, float x, float y, float z ):
 // initializations
  n_ev(n),
  x(x),
  y(y),
  z(z)
{
  // allocate a buffer for particle pointers
  part.reserve(10);

}


Event::~Event()
{
  // delete all the particle pointers
  unsigned int i=0;
  for( i=0; i < part.size(); i++ )
    delete part[i];
  // delete the pointers array
}


void Event::add( int charge, float px, float py, float pz )
{

  // check for the number of particles, if maximum reached do nothing
  // and return
  if(part.size() == part.capacity()) return;

  // create the new particle and fill with data
  Particle* p_new = new Particle{charge, px, py, pz};

  // store the new particle pointer in the array and increase counter
  part.push_back( p_new ) ;


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
  return part.size();
}

// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  if(i < part.size()) return part[i];
  else return nullptr;
}

