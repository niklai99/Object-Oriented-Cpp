#ifndef Utilities_h 
#define Utilities_h

class Event;

class Utilities {
    public:

    Utilities();
    ~Utilities();

    static double get_energy(float px, float py, float pz, float M);

    static double get_inv_mass(float px, float py, float pz, float e);

    private:

    double E;
    double m;


}

#endif
