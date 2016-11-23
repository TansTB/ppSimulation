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

Int_t MultiplicityGenerator::GetConstMultiplicity(){
  return multiplicity;
}

Int_t MultiplicityGenerator::SetConstMultiplicity(Int_t multiplicity){
  if(multiplicity>=0) this->multiplicity = multiplicity;
  else{
    std::cout << "Constant multiplicity < 0, setting multiplicity to 0" << std::endl;
    multiplicity = 0;
  }
}

Int_t MultiplicityGenerator::GetGausMultiplicity(){
  Int_t random_multiplicity = TMath::Nint(gRandom->Gaus(multiplicity,sigma));
  if (random_multiplicity>0) return random_multiplicity;
  else return GetGausMultiplicity(multiplicity,sigma);
}

void MultiplicityGenerator::SetGausMultiplicity(Double_t mean, Double_t sigma){
  this->multiplicity=mean;
  this->sigma=sigma;
}

Int_t MultiplicityGenerator::GetUniformMultiplicity(){
  Int_t random_multiplicity = gRandom->Integer(max-multiplicity+1) + multiplicity;
  return random_multiplicity;
}

void MultiplicityGenerator::SetUniformMultiplicity(Int_t min, Int_t max){
  this->multiplicity = min;
  this->max = max;
}

Int_t MultiplicityGenerator::GetCustomMultiplicity(){
  return input_hist->GetRandom();
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