#ifndef RECO_H
#define RECO_H
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
#include "TBranch.h"
#endif

const Int_t MAX_SIZE = 400; 

class Reco{
public:
   Reco(){}
   //Reco(TTree *input_tree, vector<vector<string> > configs); 
   Reco(Double_t delta_phi);  //this just in test mode
   ~Reco();

  void TreeLooper(); //loops on given tree branches and given TClonesArray
  Double_t VertexFinder(Hit * L1_candidate, Hit * L2_candidate);
  //string* RemoveWhitespaces(string& s); //parser related function

  private:
  Reco(Reco &other);
  Reco& operator=(const Reco& other);

  //General Parameters
  Hit *hit;
  Hit *L1_candidate;
  Hit *L2_candidate;
  Double_t delta_phi;
  Double_t L1_radius = 4; //just to test
  Double_t L2_radius = 7; //just to test
  
  //Tree and hit arrays
  TTree *input_tree;
  TClonesArray *ptr_L1_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &L1_hits = *ptr_L1_hits;
  TClonesArray *ptr_L2_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &L2_hits = *ptr_L2_hits;
};
#endif
