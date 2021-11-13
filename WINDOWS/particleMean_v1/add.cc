#include "Event.h"

double mass( const Event& ev );

bool add( const Event& ev, double m_min, double m_max,
          double& sum_m, double& sum_msq)
{
    // compute the invariant mass
    double m = mass( ev );

    // check if mass value is allowed
    if( (m_min <= m) && (m <= m_max) )
    {
        m -= m_min;

        // increase sums
        sum_m += m;
        sum_msq += m*m;

        return true;

    }

    return false;
}
