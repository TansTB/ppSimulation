#include "TrackGenerator.h"
#include <TMath.h>

using namespace TMath;

TrackGenerator::TrackGenerator(const char *input_file_name, const char* eta_input_hist_name){
  this->input_file_name = input_file_name;
  this->eta_input_hist_name=eta_input_hist_name;
  this->input_file = new TFile(input_file_name);
  this->eta_input_hist = (TH1D*) input_file->Get(eta_input_hist_name);
  this->eta_input_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}

TrackGenerator::~TrackGenerator(){
  if(used_hist){
    delete eta_input_hist;
  }
}


Track* TrackGenerator::GetUniformTrack(){
  Track *o_track = new Track(gRandom->Uniform(0,Pi()),gRandom->Uniform(0,2*Pi()));
  return o_track;
}

Track* TrackGenerator::GetCustomTrack(){
  Double_t th = 2*atan(exp(-eta_input_hist->GetRandom()));
  Track *o_track = new Track(th,gRandom->Uniform(0,2*Pi()));
  return o_track;
}

void TrackGenerator::SetCustomInput(const char *input_file_name, const char* eta_input_hist_name){  
   this->input_file_name = input_file_name;
  this->eta_input_hist_name=eta_input_hist_name;
  this->input_file = new TFile(input_file_name);
  this->eta_input_hist = (TH1D*) input_file->Get(eta_input_hist_name);
  this->eta_input_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}

