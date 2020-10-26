#include <cmath>
#include<iostream>

#include "Event.h"
#include "Particle.h"

double mass(const Event* ev);

bool add(const Event* ev, float m_min, float m_max, double& sum_inv_m, double& sum_squares) {

    double inv_m;

    inv_m = mass(ev);

    if(inv_m > m_min && inv_m < m_max) {
        sum_inv_m += inv_m;
        sum_squares += pow(inv_m, 2);
    }
    else return false;


    return true;
}