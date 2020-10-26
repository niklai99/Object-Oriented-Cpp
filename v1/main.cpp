#include<iostream>
#include<fstream>

//funzione per leggere i dati dal file
int read(std::ifstream &file, float &x, float &y, float &z, int *q, float *px, float *py, float *pz);

//funzione per scrivere i dati sul terminale
void dump(int n_event, int n_particles, float x, float y, float z, int *q, float *px, float *py, float *pz);

int main(int argc, char* argv[]){

    //identifier
    int id;

    //numero di particelle
    int n_particles;

    //variabili posizione di decadimento
    float x, y, z;

    //array carica elettrica
    int q[10];

    //array momenti delle particelle 
    float px[10];
    float py[10];
    float pz[10];

    
    //apro il file
    const char* file_name = argv[1];
    std::ifstream input_file(file_name, std::ifstream::in);

    //finche non arrivo alla fine del file:
    //1) leggo l'identifier del decadimenti
    //2) chiamo la funzione read che legge le cose importanti e restituisce il numero di particelle dopo il deca
    //3) chiamo la funzione dump che scrive sullo schermo i dati 
    while(!input_file.eof()) {
        input_file >> id;
        n_particles = read(input_file, x, y, z, q, px, py, pz);
        dump(id, n_particles, x, y, z, q, px, py, pz);
    }

    //chiudo il file
    input_file.close();
    return 0;
}