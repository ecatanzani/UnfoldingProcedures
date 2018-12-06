#include "MyHeader.h"

void filling_distributions(
                               TH1D &trueMass,
                               TH1D &recoMass,
                               TH1D &dataMass,
                               TTree* dTree,
                               TTree* sTree,
                               Double_t &mass,
                               Double_t &rMass,
                               Double_t &tMass
                           )
{
    for(UInt_t evC=0; evC<sTree->GetEntries(); ++evC)
    {
        sTree->GetEntry(evC);
        trueMass.Fill(tMass);
        recoMass.Fill(rMass);
    }
    
    for(UInt_t evC=0; evC<dTree->GetEntries(); ++evC)
    {
        dTree->GetEntry(evC);
        dataMass.Fill(mass);
    }
}
