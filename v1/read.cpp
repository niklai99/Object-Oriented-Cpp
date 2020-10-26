#include<iostream>
#include<fstream>

int read(std::ifstream &file, float &x, float &y, float &z, int *q, float *px, float *py, float *pz) {

    //leggo la posizione del decadimento
    file >> x >> y >> z;

    //leggo il numero di particelle dopo il decadimento
    int n_particles; 
    file >> n_particles;
    
    //per ogni particella creata leggo la carica e le 3 componenti del momento
    for(int i = 0; i < n_particles; ++i)
    {
       file >> q[i] >> px[i] >> py[i] >> pz[i];
    }

    return n_particles;
}