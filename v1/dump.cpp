#include <iostream>

void dump(int n_event, int n_particles, float x, float y, float z, int *q, float *px, float *py, float *pz) {

  // uso la formattazzione del file di testo per testare la correttezza del codice
  std::cout << n_event 
            << '\n' 
            << x << ' ' << y << ' ' << z 
            << '\n' 
            << n_particles 
            << std::endl;

  for (int i = 0; i < n_particles; ++i) std::cout << ' ' << q[i] << ' ' << px[i] << ' ' << py[i] << ' ' << pz[i] << std::endl;

  return;

}

