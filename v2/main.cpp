#include<iostream>
#include<fstream>

#include "Event.h"
#include "Particle.h"

//forward declaration della struct
struct Event;

//funzione per leggere i dati dal file
const Event* read(std::ifstream& file);

//funzione per scrivere i dati sul terminale
void dump(const Event& ev);

//funzione per liberare la memoria
void clear(const Event* ev);

/*----- MAIN -----*/
int main(int argc, char* argv[]){

    //apro il file
    const char* file_name = argv[1];
    std::ifstream input_file(file_name, std::ifstream::in);

    //creo l'evento 
    const Event* ev;

    //finchè la funzione read non ritorna un nullptr:
    //1) chiamo la funzione read ---> leggo i dati dal file
    //2) chiamo la funzione dump ---> stampo a schermo i dati
    //3) chiamo la funzione clear ---> libero la memoria 
    while ((ev = read(input_file)) != nullptr) {
        dump(*ev);
        clear(ev);
    }

    //chiudo il file
    input_file.close();
    return 0;
}