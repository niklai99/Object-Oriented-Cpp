#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <string>
#include <vector>

class Event;

class LifetimeFit {

  public:

    LifetimeFit( double min, double max, double t_min, double t_max,
                 double range_min, double range_max, double scan_step); // mass range
    ~LifetimeFit();

    bool add( const Event& ev );      // add data from a new event
    void compute();                   // compute mean and rms

    int nEvents() const;              // return number of accepted events

    double lifeTime() const; // return mean lifetime
    double lifeTimeError() const; // return mean lifetime error


  private:

    double m_min; // min mass
    double m_max; // max mass

    double t_min; // min time range
    double t_max; // max time range
    double scan_min; // min scan range
    double scan_max; // max scan range
    double scan_step; // scan step

    double mean_life;
    double rms_life;

    std::vector<double> decay_times;

};

#endif

