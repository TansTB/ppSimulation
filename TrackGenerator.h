#ifndef TRACKGENERATOR_H
#define TRACKGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Track.h"
#include "TFile.h"
#include "TH1D.h"
#include "TRandom3.h"
#endif

class TrackGenerator{
  public:
    TrackGenerator(){}
    TrackGenerator(const char* input_file_name, const char* eta_input_hist_name);
    ~TrackGenerator();

    const char* GetInputFileName(){return input_file_name;}
    const char* GetEtaInputHistName(){return eta_input_hist_name;}
    Track* GetUniformTrack();
    Track* GetCustomTrack();
    void SetCustomInput(const char* input_file_name, const char* eta_input_hist_name);
  private:
    TrackGenerator(TrackGenerator &other);
    TrackGenerator& operator=(const TrackGenerator& other);

    const char* input_file_name;
    const char* eta_input_hist_name;
    TFile *input_file;
    TH1D *eta_input_hist;
    Bool_t used_hist=0;


   
};
#endif
