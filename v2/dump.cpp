#include <iostream>

#include "Event.h"
#include "Particle.h"


/*----- DUMP -----*/
void dump(const Event& ev) {

  // uso la formattazzione del file di testo per testare la correttezza del codice
  std::cout << ev.id 
            << '\n' 
            << ev.x << ' ' << ev.y << ' ' << ev.z 
            << '\n' 
            << ev.n_particles 
            << std::endl;

  for (int i = 0; i < ev.n_particles; ++i) {

    std::cout << ' ' 
    << ev.particle[i]->q << ' ' << ev.particle[i]->px << ' ' << ev.particle[i]->py << ' ' << ev.particle[i]->pz 
    << std::endl; 

    }

  return;

}

