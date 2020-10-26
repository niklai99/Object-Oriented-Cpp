#include "Utilities.h"

Utilities::Utilities();
Utilities::~Utilities();

static double Utilities::get_energy(float px, float py, float pz, float M) {

    E = sqrt(pow(px, 2) + pow(py, 2) + pow(pz, 2) + pow(M, 2));

    return E;
}

static double Utilities::get_inv_mass(float px, float py, float pz, float e) {

    m = sqrt(pow(e, 2) - (pow(px, 2) + pow(py, 2) + pow(pz, 2)));

    return m;
}