#include "ParticleMass.h"
#include "AnalysisFactory.h"
#include "MassMean.h"
#include "TH1F.h"
#include "TFile.h"

#include <iostream>


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
    pList.reserve(2);
    pCreate("K0", 0.495, 0.500);
    pCreate("L0", 1.115, 1.116);

    return;
}


void ParticleMass::endJob()
{
    // create histogram file
    TDirectory* currentDir = gDirectory;
    TFile* file = new TFile("hist.root","CREATE");

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


void ParticleMass::process(const Event &ev)
{
    // loop over particles
    for(Particle* part: pList)
        // check if event is compatible
        if(part->m_mean->add(ev))
            // fill TH1F
            part->fun->Fill(mass(ev));

    return;
}


void ParticleMass::pCreate(const std::string& name, double m_min, double m_max)
{

    int nBins = 150;

    Particle *p = new Particle;
    p->m_mean = new MassMean(m_min,m_max);
    p->fun = new TH1F(name.c_str(), name.c_str(), nBins, m_min, m_max);

    pList.push_back(p);

}
