#include<iostream>
#include<fstream>

#include "Event.h"


/*----- READ -----*/
const Event* read(std::ifstream &file) {

    //creo l'evento
    Event* ev;

    int id;

    float x, y, z;

    int n_particles;

    int q;

    float px, py, pz;

    //finchè leggo dal file creo dinamicamente l'evento
    if (file >> id) {

        file >> x >> y >> z;
        ev = new Event(id, x, y, z);
        
        }
    //quando non leggo più dal file ritorno un nullptr
    else return nullptr;

    //leggo il numero di particelle dopo il decadimento
    file >> n_particles;
    
    //per ogni particella creata leggo la carica e le 3 componenti del momento
    for(int i = 0; i < n_particles; ++i)
    {

        //leggo carica e le tre componenti del momento
        file >> q >> px >> py >> pz;
        
        //inserisco quanto letto nella struct "madre" evento 
        ev->Add(q, px, py, pz);
    }

    return ev;
}