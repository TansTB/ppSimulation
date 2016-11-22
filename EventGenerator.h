#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_HGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TFile.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "MultiplicityGenerator.h"
#include "VtxGenerator.h"
#include "TrackGenerator.h"
#include <vector>
#include <string>
#include <algorithm>
#endif

class EventGenerator{
public:
  EventGenerator();
  EventGenerator(vector<string> configs,TTree *tree);//Sets up the event generator
  
  void NewEvent();
  void TurnOffScattering(Bool_t scattering_flag);
  
private:
  EventGenerator(const EventGenerator &other);
  EventGenerator& operator= (const EventGenerator &other);
  
  Track* MultipleScattering();
  Point* Intersection(Track* track,Double_t radius);
  void RemoveWhitespaces(string& s);
  
  Bool_t is_scattering();
  VtxGenerator vtx_gen;
  Int_t vtx_gen_mode;//vtx generator mode 0->constant 1->gaussian 2->uniform 3->custom
  MultiplicityGenerator mult_gen;
  Int_t mult_gen_mode;//mult generator mode 0->constant 1->gaussian 2->uniform 3->custom
  TrackGenerator track_gen;
  Int_t track_gen_mode;//track generator mode 0->uniform 1->custom
  Point VTX;
  TTree *tree;
  TClonesArray *ptr_BP_tracks;
  TClonesArray &BP_tracks = *ptr_BP_tracks;
  TClonesArray *ptr_BP_hits;
  TClonesArray &BP_hits = *ptr_BP_hits;
  TClonesArray *ptr_L1_hits;
  TClonesArray &L1_hits = *ptr_L1_hits;
  TClonesArray *ptr_L2_hits;  
  TClonesArray &L2_hits = *ptr_L2_hits;
}