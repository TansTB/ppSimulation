#include "Noise.h"

using namespace std;
using namespace TMath;

Noise::Noise(Int_t entries){
  this->entries=entries;        
}

Noise::~Noise(){ 
  if(used_hist){
    delete input_hist;
  }                            
  delete hit;
}

void Noise::SetParameters(Double_t zmin_detector, Double_t zmax_detector, Int_t multiplicity){
  this->zmin_detector = zmin_detector;
  this->zmax_detector = zmax_detector;
  this->multiplicity = multiplicity;
}

void Noise::NewNoise(TClonesArray *ptr_noise){
  TClonesArray &noise= *ptr_noise;
  Int_t starting_point = ptr_noise->GetLast()+1;
     for (Int_t counter=starting_point; counter<(starting_point+entries); counter++){
        new(noise[counter]) Hit(*GetUniformHits()); 
     }
}


Hit* Noise::GetUniformHits(){
  hit->SetPhi(gRandom->Uniform(-Pi(),Pi()));
  hit->SetZ(gRandom->Uniform(zmin_detector,zmax_detector));
  return hit;
}

void Noise::SetConstantEntriesNumber(Int_t entries){
  this->entries = entries;
} 

void Noise::SetCustomEntriesNumber(const char* input_file_name, const char* input_hist_name){
  this->input_file_name = input_file_name;                    
  this->input_file = new TFile(input_file_name);
  this->input_hist_name= input_hist_name;
  this->input_hist = (TH1D*) input_file->Get(input_hist_name);
  this->input_hist->SetDirectory(0);
  delete input_file;
  this->used_hist = kTRUE; 
  this->entries = input_hist->GetRandom();     
} 


