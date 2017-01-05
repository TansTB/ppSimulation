#ifndef NOISE_H
#define NOISE_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TFile.h"
#include "TH1D.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "Hit.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#endif

class Noise{
public:
   Noise(){}
   Noise(Int_t entries); 
   ~Noise();
  
  void SetParameters (Double_t zmin_detector, Double_t zmax_detector, Int_t multiplicity);
  Hit* GetUniformHits();                          //single hit generation (uniform distribution)
  void SetConstantEntriesNumber(Int_t entries);  //if constant, set entries number
  void SetCustomEntriesNumber(const char* input_file_name, const char* input_hist_name);  //if custom, set entries number
  void NewNoise(TClonesArray *ptr_noise); //adds noise hits to given hit array

  private:
  Noise(Noise &other);
  Noise& operator=(const Noise& other);

  //General Parameters
  Int_t entries;
  Int_t multiplicity = 0;                 
  Double_t zmin_detector,zmax_detector;
  Hit *hit = new Hit(-1,0,0);                    //noise hits are labelled -1

  //Input Distributions
  const char *input_file_name;
  const char *input_hist_name;
  TH1D *input_hist;
  TFile *input_file;
  Bool_t used_hist=0;

ClassDef(Noise,1);
};
#endif
