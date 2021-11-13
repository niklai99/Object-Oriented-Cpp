#ifndef PARTICLEMASS_H
#define PARTICLEMASS_H

#include <vector>
#include <string>
#include "AnalysisSteering.h"

class MassMean;
class TH1F;

class ParticleMass: public AnalysisSteering
{
   public:
        ParticleMass();
        ParticleMass(const ParticleMass &x)=delete;
        ParticleMass& operator=(const ParticleMass &x)=delete;
        ~ParticleMass() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void endJob() override;
        // function to be called for each event
        void process(const Event &ev) override;

   private:

        struct Particle
        {
           std::string part_name;
           MassMean* m_mean;
           TH1F* fun;
        };

        std::vector<Particle*> pList;

        // create a decay mode
        void pCreate(const std::string& name, double m_min, double m_max);

};


#endif
