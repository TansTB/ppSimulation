#ifndef MULTIPLICITYGENERATOR_H
#define MULTIPLICITYGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#endif

class MultiplicityGenerator{
public:
  MultiplicityGenerator(){}
  MultiplicityGenerator(const char *input_file_name, const char* input_hist_name);
  ~MultiplicityGenerator();
  
  const char* GetInputFileName(){return input_file_name;}
  const char* GetInputHistName(){return input_hist_name;}
  Int_t GetConstMultiplicity();//Returns a constant value. If multiplicity is <0, 0 is returned
  void SetConstMultiplicity(Int_t multiplicity);
  Int_t GetGausMultiplicity();//Returns a gaussian distributed integer value. If the random number is <0, 0 is returned
  void SetGausMultiplicity(Double_t mean, Double_t sigma);
  Int_t GetUniformMultiplicity();//Returns a uniform distributed integer value between min and max. Min must be >0 and <max
  void SetUniformMultiplicity(Int_t min, Int_t max);
  Int_t GetCustomMultiplicity();
  void SetCustomMultiplicity(const char* input_file_name, const char* input_hist_name);
  
private:
  MultiplicityGenerator(const MultiplicityGenerator &other);
  MultiplicityGenerator& operator=(const MultiplicityGenerator& other);
  
  const char *input_file_name;
  const char *input_hist_name;
  TFile *input_file;
  TH1D *input_hist;
  Bool_t used_hist=0;
  Double_t multiplicity,max,sigma;
  
  
};
#endif