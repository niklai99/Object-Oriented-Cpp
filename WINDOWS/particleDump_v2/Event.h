#ifndef EVENT_H
#define EVENT_H

struct Particle
{
    int charge;
    float p_x, p_y, p_z;
};

struct Event
{
    int n_ev;
    int n_p;
    float x,y,z;
    Particle** part;
};

#endif
