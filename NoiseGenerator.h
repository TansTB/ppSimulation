#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TFile.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "Hit.h"
#include "TH1D.h"
#include "TMath.h"
#include "MyParser.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#endif

const Int_t MAX_SIZE = 400; 

class NoiseGenerator{
public:
   NoiseGenerator(){}
   NoiseGenerator(const char* input_file_name, const char* z_input_hist_name, const char* phi_input_hist_name, TTree *tree, vector<vector<string> > configs);
   ~NoiseGenerator();

  Hit* GetUniformHits();  //single hit generation (uniform distribution)
  Hit* GetCustomHits();   //single hit generation (custom distribution)
  Int_t GetEntries(){return entries;}
  Double_t GetDetectorExtension(){return detector_extension;}
  void NewNoise();        //generation of all Hits and tree update 

  private:
  NoiseGenerator(NoiseGenerator &other);
  NoiseGenerator& operator=(const NoiseGenerator& other);

  string RemoveWhitespaces(string& s); //parser related function
  
  //General Parameters
  Int_t entries;
  Int_t noise_gen_mode;
  Double_t detector_extension;
  Hit *hit;
  Int_t hit_gen_mode;
  //Input Distributions
  Bool_t used_hist=0;
  const char *input_file_name;
  const char *phi_input_hist_name;
  const char *z_input_hist_name;
  TH1D *phi_input_hist;
  TH1D *z_input_hist;
  TFile *input_file;
  //Tree and hit arrays
  TTree *tree;
  TClonesArray *ptr_NO_L1_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &NO_L1_hits = *ptr_NO_L1_hits;
  TClonesArray *ptr_NO_L2_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &NO_L2_hits = *ptr_NO_L2_hits;
};
#endif
