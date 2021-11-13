#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"

#include <cmath>

double mass( const Event& ev );


LifetimeFit::LifetimeFit( float min, float max ):
 // initializations
 m_min(min),
 m_max(max)
{
    n_accepted=0;
}


LifetimeFit::~LifetimeFit()
{
}


// add data from a new event
bool LifetimeFit::add( const Event& ev )
{
    static ParticleReco* part_rec = ParticleReco::instance();
    double m = part_rec->part_m();

    // check for mass being in range
    if( (m_min <= m) && (m <= m_max) )
    {
        // update number of events and sums
        n_accepted++;
        return true;
    }

    else return false;
}


// compute mean and rms
void LifetimeFit::compute()
{}


// return number of selected events
int LifetimeFit::nEvents() const
{
    return n_accepted;
}

