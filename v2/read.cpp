#include<iostream>
#include<fstream>

#include "Event.h"
#include "Particle.h"

/*----- READ -----*/
const Event* read(std::ifstream &file) {

    //creo l'evento
    Event* ev;

    //variabile che uso per leggere l'identifier dell'evento
    int id;

    //finchè leggo dal file creo dinamicamente l'evento
    if (file >> id) ev = new Event;
    //quando non leggo più dal file ritorno un nullptr
    else return nullptr;

    //inserisco nella struct l'identifier
    ev->id = id;

    //leggo la posizione del decadimento e inserico direttamente nella struct
    file >> ev->x >> ev->y >> ev->z;

    //leggo il numero di particelle dopo il decadimento
    file >> ev->n_particles;

    //creo l'array di particelle
    ev->particle = new Particle*[ev->n_particles];
    
    //per ogni particella creata leggo la carica e le 3 componenti del momento
    for(int i = 0; i < ev->n_particles; ++i)
    {

        //creo la singola particella
        Particle* p = new Particle;

        //leggo carica e le tre componenti del momento
        file >> p->q >> p->px >> p->py >> p->pz;
        
        //inserisco quanto letto nella struct "madre" evento 
        ev->particle[i] = p;
    }

    return ev;
}