#ifndef RECO_H
#define RECO_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TFile.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "Hit.h"
#include "Point.h"
#include "TH1D.h"
#include "TMath.h"
#include "MyParser.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "TBranch.h"
#endif

const Int_t M_SIZE = 400;
class Reco{
public:
   Reco(){}
   Reco(vector<vector<string> > configs,TTree *input_tree);
//     Reco(Int_t t);
   ~Reco(){}
  
  Double_t DeltaPhiSampling();   //using simulation data, get layer 1 and layer 2 same label hit phi angle difference distribution. Output is distribution RMS.

  private:
  Reco(Reco &other);
  Reco& operator=(const Reco& other);
  
  void GetEventVertex(); //for each event, combines L1 and L2 hits according to delta_phi cut and returns the mode of candidate vertices distribution 
  Double_t GetIntersection(Hit * L1_candidate, Hit * L2_candidate); //For the provided L1,L2 hit pair, get the intersection between the reconstructed track and plane (z,0,0)

  string RemoveWhitespaces(string& s);

  //General Parameters
  Hit *L1_candidate;
  Hit *L2_candidate;
  Double_t delta_phi, intersection;
  Double_t intersection_list[100];       //how many?
  Int_t counter = 0;
  Double_t vertex_z = 0;
  Double_t z_min, z_max, z_sum;
  Double_t bin_entries = 0;
  Int_t binmax;
  Double_t my_bin_content, low_bin_content, high_bin_content;
  Double_t L1_radius;
  Double_t L2_radius; 
  Double_t dif;
  Bool_t is_reconstructed = kTRUE;

  //Tree and hit arrays
  TH1D* delta_phi_distribution = new TH1D("delta_phi","delta_phi",100,-0.005,0.005);
  TH1D* vertex_candidates = new TH1D("vertex_candidates","vertex_candidates",150,-2,2); 
  TTree *input_tree;
  TClonesArray *ptr_L1_hits = new TClonesArray("Hit",M_SIZE);
  TClonesArray &L1_hits = *ptr_L1_hits;
  TClonesArray *ptr_L2_hits = new TClonesArray("Hit",M_SIZE);
  TClonesArray &L2_hits = *ptr_L2_hits;  
  ClassDef(Reco,1);
};
#endif
