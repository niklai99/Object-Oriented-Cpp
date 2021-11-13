#include "Event.h"

void clear(const Event *ev)
{

    int i=0;
    for(i=0; i < ev->n_p; i++)
        delete ev->part[i];
    delete[] ev->part;
    delete ev;

}
