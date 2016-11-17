#ifndef MULTIPLICITYGENERATOR_H
#define MULTIPLICITYGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom3.h"
#endif

class MultiplicityGenerator{
  public:
    MultiplicityGenerator(){}
    MultiplicityGenerator(const char *input_file_name, const char* input_hist_name);
    ~MultiplicityGenerator();
        
    void SetCustomInput(const char* input_file_name, const char* input_hist_name);
    const char* GetInputFileName(){return input_file_name;}
    const char* GetInputHistName(){return input_hist_name;}
    Int_t GetConstMultiplicity(Int_t multiplicity);
    Int_t GetGausMultiplicity(Double_t mean, Double_t sigma);
    Int_t GetUniformMultiplicity(Int_t min, Int_t max);
    Int_t GetCustomMultiplicity();

  private:
    const char *input_file_name;
    const char *input_hist_name;
    TFile *input_file;
    TH1D *input_hist;
    Bool_t used_hist=0;
};
#endif