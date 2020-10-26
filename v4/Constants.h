#ifndef Constants_h
#define Constants_h

class Constants {
    public:

    const double get_massPion() const;
    const double get_massProton() const;
    const double get_massKaon() const;
    const double get_massLambda() const; 

    private:
    
    const double massPion;  
    const double massProton;
    const double massKaon;    
    const double massLambda;
}

#endif