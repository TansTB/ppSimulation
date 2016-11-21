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
#endif

class EventGenerator{
public:
  EventGenerator();
  EventGenerator(vector<strings> configs,TTree *tree);
  
  void NewEvent();
  void TurnOffScattering(Bool_t scattering_flag);
  
private:
  EventGenerator(const EventGenerator &other);
  EventGenerator& operator= (const EventGenerator &other);
  
  Track* MultipleScattering();
  Point* Intersection(Track* track,Double_t radius);
  
  Bool_t is_scattering();
  VtxGenerator vtx_gen;
  MultiplicityGenerator mult_gen;
  TrackGenerator track_gen;
  Point VTX;
  TClonesArray *ptr_BP_tracks;
  TClonesArray &BP_tracks = *ptr_BP_tracks;
  TClonesArray *ptr_BP_hits;
  TClonesArray &BP_hits = *ptr_BP_hits;
  TClonesArray *ptr_L1_hits;
  TClonesArray &L1_hits = *ptr_L1_hits;
  TClonesArray *ptr_L2_hits;  
  TClonesArray &L2_hits = *ptr_L2_hits;
}