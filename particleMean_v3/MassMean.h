#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  MassMean( float min, float max ); // mass range
  ~MassMean();

  void add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvents() const;              // return number of accepted events
  double mMean() const;             // return mean mass
  double mRMS() const;              // return rms  mass

 private:

  double m_min; // min mass
  double m_max; // max mass

  int n_accepted; // number of accepted events
  double sum_m; // sum of masses
  double sum_msq; // sum of masses square

  double mean_m; // mean mass
  double rms; // rms  mass

};

#endif

