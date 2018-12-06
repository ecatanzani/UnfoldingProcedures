#include "MyHeader.h"

int main(int argc, const char * argv[])
{
    std::string in_data_path(argv[1]);
    std::string out_data_path(argv[2]);
    
    TFile inFile(in_data_path.c_str(),"READ");
    
    TTree *dTree = nullptr,*sTree = nullptr;
    std::vector<Double_t> cFactor;
    Double_t mass,rMass,tMass;
    
    ///////// Histos
    
    /// MC Disstributions
    
    TH1D trueMass("trueMass","trueMass",100,-10,20);
    TH1D recoMass("recoMass","recoMass",100,-10,20);
    
    /// Data Distribution
    
    TH1D dataMass("dataMass","dataMass",100,-10,20);
    TH1D unfoldedMass("unfoldedMass","unFoldedMass",100,-10,20);
    
    ///////// Linking Tree branches
    
    inFile.GetObject("Data",dTree);
    inFile.GetObject("Simulation",sTree);
    
    dTree->SetBranchAddress("Mass",&mass);
    sTree->SetBranchAddress("RecoMass",&rMass);
    sTree->SetBranchAddress("TrueMass",&tMass);
    
    ///////// Filling distribution histos...
    
    cFactor.resize(true_NbinsX);
    filling_distributions(
                            trueMass,
                            recoMass,
                            dataMass,
                            dTree,
                            sTree,
                            mass,
                            rMass,
                            tMass
                          );
    
    ///////// Computing correction factor...
    
    for(UInt_t bX=1; bX<=true_NbinsX; ++bX)
        if(recoMass.GetBinContent(bX)!= 0)
            cFactor[bX-1] = trueMass.GetBinContent(bX)/recoMass.GetBinContent(bX);
        else
            cFactor[bX-1] = 0;
    
    ///////// Computing unfolded distribution...
    
    for(UInt_t bX=1; bX<=true_NbinsX; ++bX)
        unfoldedMass.SetBinContent(bX,cFactor[bX-1]*dataMass.GetBinContent(bX));
    
    ///////// Normalizing histos...
    
    normalize_histo(trueMass);
    normalize_histo(recoMass);
    normalize_histo(dataMass);
    normalize_histo(unfoldedMass);
    
    inFile.Close();
    
    ///////// Saving output distributions...
    
    TFile outFile(out_data_path.c_str(),"RECREATE");
    
    trueMass.Write();
    recoMass.Write();
    dataMass.Write();
    unfoldedMass.Write();
    
    outFile.Write();
    outFile.Close();
    
    return 0;
}
