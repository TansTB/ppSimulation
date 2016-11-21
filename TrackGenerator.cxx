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


Track* TrackGenerator::GetUniformTrack(Double_t theta_min, Double_t theta_max, Double_t phi_min, Double_t phi_max){
  Track *o_track = new Track(gRandom->Uniform(theta_min,theta_max),gRandom->Uniform(phi_min,phi_max));
  return o_track;
}

Track* TrackGenerator::GetCustomTrack(Double_t phi_min, Double_t phi_max){
  Double_t th = 2*atan(exp(-eta_input_hist->GetRandom()));
  Track *o_track = new Track(th,gRandom->Uniform(phi_min,phi_max));
  return o_track;
}

