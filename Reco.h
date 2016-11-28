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

const Int_t MAX_SIZE = 400; 

class Reco{
public:
   Reco(){}
   //Reco(TTree *input_tree, vector<vector<string> > configs); 
   Reco(Double_t delta_phi);  //this just in test mode
   ~Reco();

  Double_t GetEventVertex(); //for each event, combines L1 and L2 hits according to delta_phi cut and returns the mode of candidate vertices distribution 
  Double_t GetIntersection(Hit * L1_candidate, Hit * L2_candidate); //For the provided L1,L2 hit pair, get the intersection between the reconstructed track and plane (z,0,0)
  //Double_t GetVertex();
  //string* RemoveWhitespaces(string& s); //parser related function

  private:
  Reco(Reco &other);
  Reco& operator=(const Reco& other);
  Double_t GetMultiplicity(){return multiplicity;};

  //General Parameters
  Hit *hit;
  Hit *L1_candidate;
  Hit *L2_candidate;
  Double_t delta_phi;
  Int_t multiplicity;
  Int_t binmax;
  Double_t L1_radius = 4; //just to test
  Double_t L2_radius = 7; //just to test
  //Double_t comp[20][20];
  
  //Tree and hit arrays
  TH1D* vertex_candidates = new TH1D("vertex_candidates","vertex_candidates",300,-15,15);
  TH1D* vertex_distribution = new TH1D("vertex_distribution","vertex_distribution",100,-1.5,1.5);
  TTree *input_tree;
  TClonesArray *ptr_L1_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &L1_hits = *ptr_L1_hits;
  TClonesArray *ptr_L2_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &L2_hits = *ptr_L2_hits;
};
#endif
