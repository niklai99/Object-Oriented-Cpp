#include<iostream>
#include<fstream>
#include <cmath>

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

bool add(const Event* ev, float m_min, float m_max, double& sum_inv_m, double& sum_squares);

/*----- MAIN -----*/
int main(int argc, char* argv[]){

    //apro il file
    const char* file_name = argv[1];
    std::ifstream input_file(file_name, std::ifstream::in);

    //creo l'evento 
    const Event* ev;

    int n_events = 0;

    double sum_inv_m = 0;

    double sum_squares = 0;

    double mean;

    double rms;

    bool check;

    //finchè la funzione read non ritorna un nullptr:
    //1) chiamo la funzione read ---> leggo i dati dal file
    //2) chiamo la funzione dump ---> stampo a schermo i dati
    //3) chiamo la funzione clear ---> libero la memoria 
    while ((ev = read(input_file)) != nullptr) {

        //dump(*ev);

        check = add(ev, 0.490, 0.505, sum_inv_m, sum_squares);

        clear(ev);

        if(check) n_events++;
    }

    mean = sum_inv_m / n_events;

    rms = sqrt((sum_squares/n_events) - pow(mean, 2));

    std::cout << "\n\n" << 
    "N Events = " << n_events << "\n\n" << 
    "Mass Sum = " << sum_inv_m << "\n\n" << 
    "Squares Sum = " << sum_squares << "\n\n";

    std::cout << "\n\n" << 
    "Mean =  " << mean << "\n\n" << 
    "RMS = " << rms << "\n\n";

    //chiudo il file
    input_file.close();
    return 0;
}