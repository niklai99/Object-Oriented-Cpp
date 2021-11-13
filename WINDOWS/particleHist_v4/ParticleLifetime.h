#ifndef PARTICLEMASS_H
#define PARTICLEMASS_H

#include <vector>
#include <string>
#include "AnalysisSteering.h"
#include "util/include/ActiveObserver.h"

class LifetimeFit;
class TH1F;
class Event;

class ParticleLifetime: public AnalysisSteering,
                    public ActiveObserver<Event>
{
   public:
        ParticleLifetime( const AnalysisInfo* info );
        ParticleLifetime(const ParticleLifetime &x)=delete;
        ParticleLifetime& operator=(const ParticleLifetime &x)=delete;
        ~ParticleLifetime() override;

        // function to be called at execution start
        void beginJob() override;
        // function to be called at execution end
        void endJob() override;
        // function to be called for each event
        void update(const Event &ev) override;

   private:

        struct Particle
        {
           std::string part_name;
           LifetimeFit* lt_fit;
           TH1F* fun;
        };

        std::vector<Particle*> pList;

        // create a decay mode
        void pCreate(const std::string& name, double m_min, double m_max,
                     double timeMin, double timeMax);

};


#endif
