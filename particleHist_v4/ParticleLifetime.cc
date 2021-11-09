#include "ParticleLifetime.h"
#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "Constants.h"
#include <iostream>
#include "Event.h"
#include "LifetimeFit.h"
#include "TH1F.h"
#include "ProperTime.h"
#include <string>
#include "util/include/TFileProxy.h"


double mass( const Event& ev );


// concrete factory to create a ParticleLifetime analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "time" ) {}
  // create a ParticleLifetime when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleLifetime( info );
  }
};
// create a global ParticleLifetimeFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ParticleLifetimeFactory will be available with name "plot".
static ParticleLifetimeFactory er;



ParticleLifetime::ParticleLifetime( const AnalysisInfo* info ):
    AnalysisSteering( info )
{}


ParticleLifetime::~ParticleLifetime()
{}


void ParticleLifetime::beginJob()
{
    pList.reserve(2);
    pCreate("K0", 0.495, 0.500, 10.0, 500.0);
    pCreate("L0", 1.115, 1.116, 10.0, 1000.0);

    return;
}


void ParticleLifetime::endJob()
{
    // create histogram file
    TDirectory* currentDir = gDirectory;

    // use TFileProxy to save all histogram in the same file
    std::string name = "hist.root";
    //if(aInfo->contains("plot")) name = aInfo->value("plot");

    // open histogram file
    TFileProxy* file = new TFileProxy(name.c_str(), "CREATE");

    // TFile* file = new TFile(aInfo->value("time").c_str(),"CREATE");

    // compute mean and rms
    for(Particle* part: pList)
    {
        // compute mean and rms for current particle
        part->lt_fit->compute();

        // retrieve event number, mean and rms for current particle
        unsigned int n_part = part->lt_fit->nEvents();

        // print results on screen
        std::cout << "(decay time) n_part\t" << n_part << std::endl;

        // write TH1F
        part->fun->Write();

    }

    // close file
    file->Close();
    delete file;

    currentDir->cd();

    return;
}


void ParticleLifetime::update(const Event &ev)
{
    static ProperTime* time_rec = ProperTime::instance();

    // loop over particles
    for(Particle* part: pList)
        // check if event is compatible
        if(part->lt_fit->add(ev))
            // fill TH1F
            part->fun->Fill(time_rec->decayTime());

    return;
}


void ParticleLifetime::pCreate(const std::string& name, double m_min,
                               double m_max, double timeMin, double timeMax)
{

    int nBins = 150;

    Particle *p = new Particle;
    p->lt_fit = new LifetimeFit(m_min,m_max);
    std::string h_name = "time"+name;
    p->fun = new TH1F(h_name.c_str(), h_name.c_str(), nBins, timeMin, timeMax);

    pList.push_back(p);

}
