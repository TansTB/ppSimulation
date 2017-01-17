#ifndef TRACKGENERATOR_H
#define TRACKGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Track.h"
#include "TFile.h"
#include "TH1D.h"
#include "TRandom3.h"
#include "TMath.h"
#endif

class TrackGenerator{
  public:
    TrackGenerator(){this->track = new Track();}
    TrackGenerator(const char* input_file_name, const char* eta_input_hist_name);
    ~TrackGenerator();

    const char* GetInputFileName(){return input_file_name;}
    const char* GetEtaInputHistName(){return eta_input_hist_name;}
    Track* GetUniformTrack();//Returns a track between thetamin and thetamax, 0<thetamin<thetamax<Pi
    void SetUniformTrack(Double_t thetamin,Double_t thetamax);
    Track* GetCustomTrack();//Returns a track with eta between -2 and 2, from the eta_input_hist
    void SetCustomTrack(const char* input_file_name, const char* eta_input_hist_name);
  private:
    TrackGenerator(TrackGenerator &other);
    TrackGenerator& operator=(const TrackGenerator& other);

    Track *track;
    const char *input_file_name;
    const char *eta_input_hist_name;
    TFile *input_file;
    TH1D *eta_input_hist;
    Bool_t used_hist=0;
    Double_t thetamin,thetamax;  

};
#endif
