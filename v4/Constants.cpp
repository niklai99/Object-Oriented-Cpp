#include "Constants.h"

Constants::Constants(){
    massPion(0.1395706),
    massProton(0.938272),
    massKaon(0.497611),
    massLambda(1.115683)
    }

Constants::~Constants()

const double Constants::get_massKaon() const {
    return massKaon;
}

const double Constants::get_massLambda() const {
    return massLambda;
}

const double Constants::get_massPion() const {
    return massPion;
}

const double Constants::get_massProton() const {
    return massProton;
}