#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "QuadraticFitter.h"
#include <cmath>

double mass( const Event& ev );


LifetimeFit::LifetimeFit(double min, double max,
                         double t_min, double t_max,
                         double scan_min, double scan_max, double scan_step):
    m_min(min), m_max(max),
    t_min(t_min), t_max(t_max),
    scan_min(scan_min), scan_max(scan_max), scan_step(scan_step)
{}


LifetimeFit::~LifetimeFit()
{}


// add data from a new event
bool LifetimeFit::add( const Event& ev )
{
    static ParticleReco* part_rec = ParticleReco::instance();
    static ProperTime* proper_t = ProperTime::instance();
    double m = part_rec->part_m();
    double time = proper_t->decayTime();

    // check for mass being in range
    if( (m_min <= m) && (m <= m_max) )
    {
        // check for time being in range
        if( (t_min <= time) && (time <= t_max) )
        {
            decay_times.push_back(time);
            return true;
        }
    }
    return false;
}


// compute mean and rms
void LifetimeFit::compute()
{
    // perform a max. likelihood fit
    QuadraticFitter qFit;
    for(double t_s = scan_min; t_s < scan_max; t_s += scan_step)
    {
        double L_t = 0;
        double t_i = 0;
        unsigned int i = 0;
        for(i=0; i < decay_times.size(); i++)
        {
            t_i = decay_times[i];
            L_t += ( ( t_i / t_s ) + log( t_s ) +
                     log( exp( -t_min / t_s ) - exp( -t_max /t_s ) ) );
        }
        qFit.add(t_s,L_t);
    }
    mean_life  = - qFit.b() / ( 2. * qFit.c() );
    rms_life = 1. / sqrt( 2. * qFit.c() );

}


// return number of selected events
int LifetimeFit::nEvents() const
{ return decay_times.size(); }

// return mean life time
double LifetimeFit::lifeTime() const
{ return mean_life; }
// return life time error
double LifetimeFit::lifeTimeError() const
{ return rms_life; }
