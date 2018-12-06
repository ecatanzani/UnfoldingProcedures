#include "MyHeader.h"

void link_data(
                TFile &inFile,
                TTree* dTree,
                TTree* sTree,
                const std::string data_path,
                Double_t &mass,
                Double_t &rMass,
                Double_t &tMass
               )
{
    inFile.GetObject("Data",dTree);
    inFile.GetObject("Simulation",sTree);
    
    dTree->SetBranchAddress("Mass",&mass);
    sTree->SetBranchAddress("RecoMass",&rMass);
    sTree->SetBranchAddress("TrueMass",&tMass);
}
