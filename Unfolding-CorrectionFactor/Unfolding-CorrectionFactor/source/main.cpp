#include "MyHeader.h"

int main(int argc, const char * argv[])
{
    std::string in_data_path(argv[1]);
    std::string out_data_path(argv[2]);

    TTree *dTree = nullptr,*sTree = nullptr;
    std::vector<Double_t> cFactor;
    Double_t mass,rMass,tMass;
    
    ///////// Histos
    
    /// MC Disstributions
    
    TH1D trueMass("trueMass","trueMass",100,-10,20);
    TH1D recoMass("recoMass","recoMass",100,-10,20);
    
    /// Data Distribution
    
    TH1D dataMass("dataMass","dataMass",100,-10,20);
    dataMass.Sumw2();
    
    TH1D unfoldedMass("unfoldedMass","unFoldedMass",100,-10,20);
    
    /// Correction Factor
    
    TH1D hcFactor("hcFactor","hcFactor",10,0,2);
    
    //////////////////////////////
    
    TFile inFile(in_data_path.c_str(),"READ");
    
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
    {
        if(recoMass.GetBinContent(bX)!= 0)
            cFactor[bX-1] = trueMass.GetBinContent(bX)/recoMass.GetBinContent(bX);
        else
            cFactor[bX-1] = 0;
        hcFactor.Fill(cFactor[bX-1]);
    }
    
    ///////// Computing unfolded distribution...
    
    for(UInt_t bX=1; bX<=true_NbinsX; ++bX)
    {
        //// Raw method to scale and setting errors ... ;-(
        unfoldedMass.SetBinContent(bX,cFactor[bX-1]*dataMass.GetBinContent(bX));
        unfoldedMass.SetBinError(bX,cFactor[bX-1]*TMath::Sqrt(dataMass.GetBinContent(bX)));
    }
        
    ///////// Normalizing histos...
    
    TH1D* n_trueMass = (TH1D*) trueMass.Clone("n_trueMass");
    TH1D* n_recoMass = (TH1D*) recoMass.Clone("n_recoMass");
    TH1D* n_dataMass = (TH1D*) dataMass.Clone("n_dataMass");
    TH1D* n_unfoldedMass = (TH1D*) unfoldedMass.Clone("n_unfoldedMass");
    
    n_trueMass->SetDirectory(0);
    n_recoMass->SetDirectory(0);
    n_dataMass->SetDirectory(0);
    n_unfoldedMass->SetDirectory(0);
    
    normalize_histo(n_trueMass);
    normalize_histo(n_recoMass);
    normalize_histo(n_dataMass);
    normalize_histo(n_unfoldedMass);
    
    inFile.Close();
    
    ///////// Saving output distributions...
    
    TFile outFile(out_data_path.c_str(),"RECREATE");
    
    trueMass.Write();
    recoMass.Write();
    dataMass.Write();
    unfoldedMass.Write();
    
    n_trueMass->Write();
    n_recoMass->Write();
    n_dataMass->Write();
    n_unfoldedMass->Write();
    
    hcFactor.Write();
    
    outFile.Write();
    outFile.Close();
    
    return 0;
}
