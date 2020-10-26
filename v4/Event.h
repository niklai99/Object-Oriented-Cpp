#ifndef Event_h
#define Event_h

class Event {

 public:

  Event( int n, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( electric charge and x, y, z momentum components )
  struct Particle {

    //carica elettrica
    int q;

    //le tre componenti del momento della singola particella
    float px;
    float py;
    float pz;

  };
  typedef const Particle* part_ptr;

  // add a particle to the event
  void add( int charge, float px, float py, float pz );

  // get event id.
  int eventNumber() const;
  // get decay point coordinates
  float x() const;
  float y() const;
  float z() const;
  // get number of particles
  unsigned int nParticles();
  // get particle
  part_ptr particle( unsigned int i ) const;

 private:

  // event-specific informations:
  int id; // event id
  float x, y, z; // decay point

  // particles: number and array of pointers
  int n_particles;
  Particle** particle;

  const int max_particle;

};

#endif

