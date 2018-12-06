#ifndef MyHeader_h
#define MyHeader_h

#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"


////////////// User functions

extern void link_data(
                        TFile &inFile,
                        TTree* dTree,
                        TTree* sTree,
                        const std::string data_path,
                        Double_t &mass,
                        Double_t &rMass,
                        Double_t &tMass
                      );


#endif /* MyHeader_h */
