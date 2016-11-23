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

const Int_t MAX_SIZE = 400;

class EventGenerator{
public:
  EventGenerator();
  EventGenerator(vector<string> configs,TTree *tree);//Sets up the event generator
  
  void NewEvent();
  
private:
  EventGenerator(const EventGenerator &other);
  EventGenerator& operator= (const EventGenerator &other);
  
  Track* BeMultipleScattering(Track* track,Double_t thickness);
  Bool_t Intersection(Point* vertex,Track* track,Double_t radius,Hit* intersection);
  Bool_t Intersection(Hit layer_hit,Int_t layer_number,Track* track,Double_t radius,Hit* intersection);
  void RemoveWhitespaces(string& s);
  
  Bool_t is_scattering;
  VtxGenerator vtx_gen;
  Int_t vtx_gen_mode;//vtx generator mode 0->constant 1->gaussian 2->uniform 3->custom
  MultiplicityGenerator mult_gen;
  Int_t mult_gen_mode;//mult generator mode 0->constant 1->gaussian 2->uniform 3->custom
  TrackGenerator track_gen;
  Int_t track_gen_mode;//track generator mode 0->uniform 1->custom
  Point *VTX;
  Int_t *multiplicity;
  TTree *tree;
  TClonesArray *ptr_tracks = new TClonesArray("Track",MAX_SIZE);
  TClonesArray &tracks = *ptr_tracks;
  TClonesArray *ptr_BP_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &BP_hits = *ptr_BP_hits;
  TClonesArray *ptr_L1_hits = new TClonesArray("Hit",MAX_SIZE);
  TClonesArray &L1_hits = *ptr_L1_hits;
  TClonesArray *ptr_L2_hits = new TClonesArray("Hit",MAX_SIZE);  
  TClonesArray &L2_hits = *ptr_L2_hits;
  Double_t BP_radius,BP_thickness,L1_radius,L1_thickness,L2_radius,zmax_detector,zmin_detector;
}