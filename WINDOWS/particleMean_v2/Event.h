#ifndef Event_h
#define Event_h

class Event {

 public:

  Event( int n, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( electric charge and x,y,z momentum components )
  struct Particle {
    int charge;
    float p_x, p_y, p_z;
  };
  typedef const Particle* part_ptr;

  // add a particle to the event
  void add( int charge, float px, float py, float pz );

  // get event id.
  int eventNumber() const;
  // get decay point coordinates
  float coord_x() const;
  float coord_y() const;
  float coord_z() const;
  // get number of particles
  int nParticles() const;
  // get particle
  part_ptr particle( unsigned int i ) const;

 private:

  // event-specific informations:
  int n_ev; // event id
  float x, y, z; // decay point

  // particles: number and array of pointers
  unsigned int n_p;
  Particle** part;

  // maximum number of particles
  unsigned int n_max=10;

};

#endif

