#include "Event.h"
#include "Particle.h"


/*----- CLEAR -----*/
void clear(const Event* ev) {

    //libero la memoria delle singole particelle create dinamicamente
    for(int i = 0; i < ev->n_particles; ++i) {

        delete ev->particle[i];
  
    }

    //libero la memoria dell'array di particelle creato dinamicamente
    delete[] ev->particle;

    //libero la memoria dell'evento
    delete ev;

    return;
}

