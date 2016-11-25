#include "NoiseGenerator.h"

using namespace std;
using namespace TMath;

NoiseGenerator::NoiseGenerator(const char* input_file_name, const char* z_input_hist_name, const char* phi_input_hist_name, TTree *tree, vector<vector<string> > configs){
  
  //Input Files Management
  this->input_file_name = input_file_name;
  this->input_file = new TFile(input_file_name);
  this->phi_input_hist_name=phi_input_hist_name;
  this->z_input_hist_name=phi_input_hist_name;
  this->phi_input_hist = (TH1D*) input_file->Get(phi_input_hist_name);
  this->phi_input_hist->SetDirectory(0);
  this->z_input_hist = (TH1D*) input_file->Get(z_input_hist_name);
  this->z_input_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;

  //Generator Configuration
  this->tree = tree;
  this->entries = stod(configs.at(34).at(1));
  this->detector_extension = stod(configs.at(32).at(1));
  if(RemoveWhitespaces(configs.at(35).at(1))== "uniform"){
    noise_gen_mode=0;
  }
  if(RemoveWhitespaces(configs.at(35).at(1))== "custom"){
    noise_gen_mode=1;
  }
  
  //Tree management and hit generation
  this->hit = new Hit();
  this->hit->SetLabel(-1);  //noise hits are labelled -1
  tree->Branch("NO_L1_Hits",&ptr_NO_L1_hits); 
  tree->Branch("NO_L2_Hits",&ptr_NO_L2_hits);
  NewNoise();
}

NoiseGenerator::~NoiseGenerator(){
  if(used_hist){
    delete phi_input_hist;
    delete z_input_hist;
  }
  delete hit;
}

void NoiseGenerator::NewNoise(){
  switch(noise_gen_mode){
    case 0 : { 
      for (Int_t j=0; j<GetEntries(); j++){
        new(NO_L1_hits[j]) Hit(*GetUniformHits());
        new(NO_L2_hits[j]) Hit(*GetUniformHits());
      }
    }
      break;
    case 1 : {
      for (Int_t j=0; j<GetEntries(); j++){
        new(NO_L1_hits[j]) Hit(*GetCustomHits());
        new(NO_L2_hits[j]) Hit(*GetCustomHits());
      }
    }
  }
  tree->Fill();
  ptr_NO_L1_hits->Clear();
  ptr_NO_L2_hits->Clear();
}

Hit* NoiseGenerator::GetUniformHits(){
  hit->SetPhi(gRandom->Uniform(0,2*Pi()));
  Double_t ext = GetDetectorExtension();
  hit->SetZ(gRandom->Uniform(-ext/2,ext/2));
  return hit;
}

Hit* NoiseGenerator::GetCustomHits(){
  hit->SetPhi(phi_input_hist->GetRandom());
  hit->SetZ(z_input_hist->GetRandom());
  return hit;
}

string NoiseGenerator::RemoveWhitespaces(string& s){
  s.erase(std::remove_if(s.begin(),s.end(),[](char c){return std::isspace(static_cast<unsigned char>(c));}),s.end());
  return s;
}


