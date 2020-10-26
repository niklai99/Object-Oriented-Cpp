#ifndef Event_h
#define Event_h

#include "Particle.h"

struct Event {

  //identifier dell'evento
  int id;

  //coordinate del decadimento
  float x;
  float y;
  float z;

  //numero di particelle dopo il decadimento
  int n_particles;

  //array di puntatori 
  Particle** particle = new Particle*;

};

#endif

