#ifndef ParticleReco_h
#define ParticleReco_h

#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"

class Event;

class ParticleReco: public Singleton<ParticleReco>,
                    public LazyObserver<Event> {

  friend class Singleton<ParticleReco>;

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

 private:

  // private constructor and destructor for singleton
  ParticleReco();
  // deleted copy constructor and assignment to prevent unadvertent copy
  ParticleReco           ( const ParticleReco& x ) = delete;
  ParticleReco& operator=( const ParticleReco& x ) = delete;

  // destructor
  ~ParticleReco() override;

  // particle type
  ParticleType type;
  // particle energy
  double energy;
  // particle mass
  double mass;

};

#endif

