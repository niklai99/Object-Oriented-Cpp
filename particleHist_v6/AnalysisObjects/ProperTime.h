#ifndef ProperTime_h
#define ProperTime_h

#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"

class Event;

class ProperTime: public Singleton<ProperTime>,
                    public LazyObserver<Event> {

  friend class Singleton<ProperTime>;

 public:

  // particle types
  enum ParticleType { K0, Lambda0, unknown };

  // recompute informations for new event
  void update( const Event& ev ) override;

  // return particle type
  ParticleType part_type();
  // return particle energy
  double part_en();
  // return particle mass
  double part_m();
  // return decat time
  double decayTime();

 private:

  // private constructor and destructor for singleton
  ProperTime();
  // deleted copy constructor and assignment to prevent unadvertent copy
  ProperTime           ( const ProperTime& x ) = delete;
  ProperTime& operator=( const ProperTime& x ) = delete;

  // destructor
  ~ProperTime() override;

  // particle type
  ParticleType type;
  // particle energy
  double energy;
  // particle mass
  double mass;

  double time;

};

#endif

