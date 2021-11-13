#include "MassMean.h"
#include "Event.h"

#include <cmath>

double mass( const Event& ev );


MassMean::MassMean( float min, float max ):
 // initializations
 m_min(min),
 m_max(max)
{
    n_accepted=0;
    sum_m=0;
    sum_msq=0;

}


MassMean::~MassMean()
{
}


// add data from a new event
bool MassMean::add( const Event& ev )
{
    double m = mass(ev);

    // check for mass being in range
    if( (m_min <= m) && (m <= m_max) )
    {
        // update number of events and sums
        n_accepted++;

        // increase sums
        m -= m_min;
        sum_m += m;
        sum_msq += m*m;

        return true;

    }

    else return false;

}


// compute mean and rms
void MassMean::compute()
{
  // compute mean
  mean_m = sum_m *1./ n_accepted;

  // compute rms
  double ms = sum_msq *1./ n_accepted - mean_m*mean_m;
  ms > 0? rms=sqrt(ms) : rms=0;

  mean_m += m_min;

}


// return number of selected events
int MassMean::nEvents() const
{
    return n_accepted;
}

// return mean and rms
double MassMean::mMean() const
{
    return mean_m;
}

double MassMean::mRMS() const
{
    return rms;
}
