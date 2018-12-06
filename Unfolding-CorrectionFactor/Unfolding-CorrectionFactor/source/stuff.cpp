#include "MyHeader.h"

void normalize_histo(TH1D &histo)
{
    Double_t sum = 0;
    for(UInt_t bX=1; bX<= true_NbinsX; ++bX)
        sum += histo.GetBinWidth(bX)*histo.GetBinContent(bX);
    
    for(UInt_t bX=1; bX<= true_NbinsX; ++bX)
        histo.SetBinContent(bX,histo.GetBinContent(bX)/sum);

}
