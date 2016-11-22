#include "VtxGenerator.h"

VtxGenerator::VtxGenerator(const char* input_file_name, const char* xinput_hist_name,const char* yinput_hist_name,const char* zinput_hist_name){
  this->input_file_name = input_file_name;
  this->input_hist_name=input_hist_name;
  this->input_file = new TFile(input_file_name);
  this->xinput_hist = (TH1D*) input_file->Get(xinput_hist_name);
  this->yinput_hist = (TH1D*) input_file->Get(yinput_hist_name);
  this->zinput_hist = (TH1D*) input_file->Get(zinput_hist_name);
  this->xinput_hist->SetDirectory(0);
  this->yinput_hist->SetDirectory(0);
  this->zinput_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}

VtxGenerator::~VtxGenerator(){
  if(used_hist){
    delete xinput_hist;
    delete yinput_hist;
    delete zinput_hist;
  }
}

void VtxGenerator::SetCustomInput(const char* input_file_name, const char* xinput_hist_name,const char* yinput_hist_name,const char* zinput_hist_name){
  this->input_file_name = input_file_name;
  this->input_hist_name=input_hist_name;   
  this->input_file = new TFile(input_file_name);
  this->xinput_hist = (TH1D*) input_file->Get(xinput_hist_name);
  this->yinput_hist = (TH1D*) input_file->Get(yinput_hist_name);
  this->zinput_hist = (TH1D*) input_file->Get(zinput_hist_name);
  this->xinput_hist->SetDirectory(0);
  this->yinput_hist->SetDirectory(0);
  this->zinput_hist->SetDirectory(0);
  this->input_file->Close();
  delete input_file;
  this->used_hist = kTRUE;
}

Point* VtxGenerator::GetConstVtx(Double_t x, Double_t y, Double_t z){
  Point *o_point = new Point(x,y,z);
  return o_point;  
}

Point* VtxGenerator::GetGausVtx(Double_t x, Double_t sx, Double_t y, Double_t sy, Double_t z, Double_t sz){
  Point *o_point = new Point(gRandom->Gaus(x,sx),gRandom->Gaus(y,sy),gRandom->Gaus(z,sz));
  return o_point;
}

Point* VtxGenerator::GetUniformVtx(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Double_t zmin, Double_t zmax){
  Point *o_point = new Point(gRandom->Uniform(xmin,xmax),gRandom->Uniform(ymin,ymax),gRandom->Uniform(zmin,zmax));
  return o_point;
}

Point* VtxGenerator::GetCustomVtx(){
  Point *o_point = new Point(xinput_hist->GetRandom(),yinput_hist->GetRandom(),zinput_hist->GetRandom(),);
  return o_point;
}