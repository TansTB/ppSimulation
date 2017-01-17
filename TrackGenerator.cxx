#include "TrackGenerator.h"

using namespace TMath;

TrackGenerator::TrackGenerator(const char *input_file_name, const char* eta_input_hist_name){
  this->input_file_name = input_file_name;
  this->eta_input_hist_name=eta_input_hist_name;
  this->input_file = new TFile(input_file_name);
  this->eta_input_hist = (TH1D*) input_file->Get(eta_input_hist_name);
  this->eta_input_hist->SetDirectory(0);
  for(Int_t i=0;i<eta_input_hist->GetSize();i++)if((eta_input_hist->GetBinCenter(i)<-2)||(eta_input_hist->GetBinCenter(i)>2))eta_input_hist->SetBinContent(i,0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
  this->track = new Track();
}

TrackGenerator::~TrackGenerator(){
  if(used_hist){
    delete eta_input_hist;
  }
  delete track;
}

Track* TrackGenerator::GetUniformTrack(){
  track->SetTheta(gRandom->Uniform(thetamin,thetamax));
  track->SetPhi(gRandom->Uniform(-Pi(),Pi()));
  return track;
}

void TrackGenerator::SetUniformTrack(Double_t thetamin,Double_t thetamax){
  this->thetamin = thetamin;
  this->thetamax = thetamax;
}

Track* TrackGenerator::GetCustomTrack(){
  Double_t th = 2*atan(exp(-eta_input_hist->GetRandom()));
  track->SetTheta(th);
  track->SetPhi(gRandom->Uniform(-Pi(),Pi()));
  return track;
}

void TrackGenerator::SetCustomTrack(const char *input_file_name, const char* eta_input_hist_name){  
   this->input_file_name = input_file_name;
  this->eta_input_hist_name=eta_input_hist_name;
  this->input_file = new TFile(input_file_name);
  this->eta_input_hist = (TH1D*) input_file->Get(eta_input_hist_name);
  this->eta_input_hist->SetDirectory(0);
  for(Int_t i=0;i<eta_input_hist->GetSize();i++)if((eta_input_hist->GetBinCenter(i)<-2)||(eta_input_hist->GetBinCenter(i)>2))eta_input_hist->SetBinContent(i,0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}
