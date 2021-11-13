#include "ParticleMass.h"
#include "../AnalysisFramework/AnalysisFactory.h"
#include "../AnalysisObjects/MassMean.h"
#include "TH1F.h"
#include "../AnalysisObjects/ParticleReco.h"
#include "util/include/TFileProxy.h"
#include "../AnalysisFramework/AnalysisInfo.h"

#include <iostream>
#include <fstream>


double mass( const Event& ev );


// concrete factory to create a ParticleMass analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
  // create a ParticleMass when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleMass( info );
  }
};
// create a global ParticleMassFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ParticleMassFactory will be available with name "plot".
static ParticleMassFactory er;



ParticleMass::ParticleMass( const AnalysisInfo* info ):
    AnalysisSteering( info )
{}


ParticleMass::~ParticleMass()
{}


void ParticleMass::beginJob()
{

    // read ranges from a text file
    std::ifstream file(aInfo->value("massRanges").c_str());
    std::string name;
    double min;
    double max;
    pList.reserve(2);
    while (file >> name >> min >> max)
    {
       pCreate(name, min, max);
    }

    return;
}


void ParticleMass::endJob()
{
    // create histogram file
    TDirectory* currentDir = gDirectory;

    // use TFileProxy to save all histogram in the same file
    std::string name = "hist.root";

    TFileProxy* file = new TFileProxy(name.c_str(), "CREATE");

    // compute mean and rms
    for(Particle* part: pList)
    {
        // compute mean and rms for current particle
        part->m_mean->compute();

        // retrieve event number, mean and rms for current particle
        unsigned int n_part = part->m_mean->nEvents();
        double mean = part->m_mean->mMean();
        double rms = part->m_mean->mRMS();

        // print results on screen
        std::cout << "n_part\t" << n_part << "\t" << "mean\t" << mean <<  "\t"
                  << "rms\t" << rms << std::endl;

        // write TH1F
        part->fun->Write();

    }

    // close file
    file->Close();
    delete file;

    currentDir->cd();

    return;
}


void ParticleMass::update(const Event &ev)
{
    static ParticleReco* part_rec = ParticleReco::instance();
    double m = part_rec->part_m();

    // loop over particles
    for(Particle* part: pList)
        // check if event is compatible
        if(part->m_mean->add(ev))
            // fill TH1F
            part->fun->Fill(m);

    return;
}


void ParticleMass::pCreate(const std::string& name, double m_min, double m_max)
{

    int nBins = 150;

    Particle *p = new Particle;
    p->m_mean = new MassMean(m_min,m_max);
    std::string h_name = "mass"+name;
    p->fun = new TH1F(h_name.c_str(), h_name.c_str(), nBins, m_min, m_max);

    pList.push_back(p);

}
