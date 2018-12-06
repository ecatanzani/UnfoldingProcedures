#ifndef MyHeader_h
#define MyHeader_h

#include <iostream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#define true_NbinsX 100

////////////// User functions

extern void filling_distributions(
                                    TH1D &trueMass,
                                    TH1D &recoMass,
                                    TH1D &dataMass,
                                    TTree* dTree,
                                    TTree* sTree,
                                    Double_t &mass,
                                    Double_t &rMass,
                                    Double_t &tMass
                                  );

extern void normalize_histo(TH1D &histo);

#endif /* MyHeader_h */
