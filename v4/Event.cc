#include "Event.h"

Event::Event( int n, float x, float y, float z ):
  // initializations
  id(n),
  x(0),
  y(0),
  z(0),
  n_particles(0),
  max_particle(10) {
    // allocate a buffer for particle pointers
    particle = new part_ptr[max_particle];
}


Event::~Event() {
  // delete all the particle pointers
  for(int i = 0; i < max_particle; ++i) {
    delete particle[i];
  }

  // delete the pointers array
  delete[] particle;
}


void Event::add( int charge, float px, float py, float pz ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  int j = 0;

  while(j < n_particles) {
    // create the new particle and fill with data
    part_ptr p = new Particle;
    p->q = charge;
    p->px = px;
    p->py = py;
    p->pz = pz;

    // store the new particle pointer in the array and increase counter
    particle[j] = p;
    j++;
  }

  return;

}


// get event id.
int Event::eventNumber() const {
  return id;
}


// get decay point coordinates
float Event::x() const {
  return x;
}

float Event::y() const {
  return y;
}

float Event::x() const {
  return z;
}


// get number of particles
unsigned int Event::nParticles() {
  return n_particles;
}


// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  return particle[i];
}

