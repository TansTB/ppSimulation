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
  EventGenerator(vector<strings>);
  
  
private:
  EventGenerator(const EventGenerator &other);
  EventGenerator& operator= (const EventGenerator &other);
  Track* MultipleScattering();
}