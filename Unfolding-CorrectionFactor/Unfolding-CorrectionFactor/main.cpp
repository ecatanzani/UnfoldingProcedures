#include "MyHeader.h"

int main(int argc, const char * argv[])
{
    std::string data_path(argv[1]);
    TFile inFile(data_path.c_str(),"READ");
    TTree *dTree = nullptr,*sTree = nullptr;
    
    Double_t mass,rMass,tMass;
    
    
    link_data(
                inFile,
                dTree,
                sTree,
                data_path,
                mass,
                rMass,
                tMass
              );
    
    for(Long64_t evC=0; evC<dTree->GetEntries(); ++evC)
    {
        
        
    }
    
    return 0;
}
