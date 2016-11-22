#include <iostream>
#include "MultiplicityGenerator.h"

MultiplicityGenerator::MultiplicityGenerator(const char *input_file_name, const char* input_hist_name){
  this->input_file_name = input_file_name;
  this->input_hist_name=input_hist_name;
  this->input_file = new TFile(input_file_name);
  this->input_hist = (TH1D*) input_file->Get(input_hist_name);
  this->input_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}

MultiplicityGenerator::~MultiplicityGenerator(){
  if(used_hist)delete input_hist;
}

void MultiplicityGenerator::SetCustomInput(const char* input_file_name, const char* input_hist_name){
  this->input_file_name = input_file_name;
  this->input_hist_name=input_hist_name;   
  this->input_file = new TFile(input_file_name);
  this->input_hist = (TH1D*) input_file->Get(input_hist_name);
  this->input_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}

Int_t MultiplicityGenerator::GetConstMultiplicity(Int_t multiplicity){
  if(multiplicity>0)return multiplicity;
  else{
    std::cout << "Constant multiplicity <= 0, returning 0" << std::endl;
    return 0;
  }
}


Int_t MultiplicityGenerator::GetGausMultiplicity(Double_t mean, Double_t sigma){
  Int_t multiplicity = TMath::Nint(gRandom->Gaus(mean,sigma));
  if (multiplicity>0) return multiplicity;
  else return GetGausMultiplicity(mean,sigma);
}

Int_t MultiplicityGenerator::GetUniformMultiplicity(Int_t min, Int_t max){
  Int_t multiplicity = gRandom->Integer(max-min+1) + min;
  return multiplicity;
}

Int_t MultiplicityGenerator::GetCustomMultiplicity(){
  return input_hist->GetRandom();
}

