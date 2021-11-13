#include "ParticleMass.h"
#include "MassMean.h"

#include <iostream>

ParticleMass::ParticleMass()
{
}
ParticleMass::~ParticleMass()
{
}

void ParticleMass::beginJob()
{
    pList.reserve(2);

    pList.push_back(new MassMean(0.495, 0.500));
    pList.push_back(new MassMean(1.115, 1.116));

    return;
}

void ParticleMass::endJob()
{
    // compute mean and rms
    for(MassMean* mMean: pList)
    {
        mMean->compute();

        double mean = mMean->mMean();
        double rms = mMean->mRMS();
        std::cout << "mean\t" << mean <<  "\t" << "rms\t" << rms << std::endl;
    }

    return;
}

void ParticleMass::process(const Event &ev)
{
    for(MassMean* mMean: pList) mMean->add(ev);

    return;
}
