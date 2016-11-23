#include "VtxGenerator.h"

VtxGenerator::VtxGenerator(const char* xinput_file_name,const char* yinput_file_name,const char* zinput_file_name, const char* xinput_hist_name,const char* yinput_hist_name,const char* zinput_hist_name){
  this->xinput_file_name = xinput_file_name;
  this->yinput_file_name = yinput_file_name;
  this->zinput_file_name = zinput_file_name;
  this->xinput_hist_name=xinput_hist_name;   
  this->yinput_hist_name=yinput_hist_name;   
  this->zinput_hist_name=zinput_hist_name;  
  this->xinput_file = new TFile(xinput_file_name);
  this->yinput_file = new TFile(yinput_file_name);
  this->zinput_file = new TFile(zinput_file_name);
  this->xinput_hist = (TH1D*) xinput_file->Get(xinput_hist_name);
  this->yinput_hist = (TH1D*) yinput_file->Get(yinput_hist_name);
  this->zinput_hist = (TH1D*) zinput_file->Get(zinput_hist_name);
  this->xinput_hist->SetDirectory(0);
  this->yinput_hist->SetDirectory(0);
  this->zinput_hist->SetDirectory(0);
  this->xinput_file->Close();
  this->yinput_file->Close();
  this->zinput_file->Close();
  delete xinput_file;
  delete yinput_file;
  delete zinput_file;
  this->used_hist = kTRUE;
  this->vtx = new Point();
}

VtxGenerator::~VtxGenerator(){
  if(used_hist){
    delete xinput_hist;
    delete yinput_hist;
    delete zinput_hist;
  }
  delete vtx;
}

Point* VtxGenerator::GetConstVtx(){
  vtx->SetX(x);
  vtx->SetY(y);
  vtx->SetZ(z);
  return vtx;  
}

void VtxGenerator::SetConstVtx(Double_t x, Double_t y, Double_t z){
  this->x = x;
  this->y = y;
  this->z = z;
} 

Point* VtxGenerator::GetGausVtx(){
  vtx->SetX(gRandom->Gaus(x,sx));
  vtx->SetY(gRandom->Gaus(y,sy));
  vtx->SetZ(gRandom->Gaus(z,sz));
  return vtx;
}

void VtxGenerator::SetGausVtx(Double_t x, Double_t sx, Double_t y, Double_t sy, Double_t z, Double_t sz){
  this->x = x;
  this->y = y;
  this->z = z;
  this->sx = sx;
  this->sy = sy;
  this->sz = sz;  
}

Point* VtxGenerator::GetUniformVtx(){
  vtx->SetX(gRandom->Uniform(x,xmax));
  vtx->SetY(gRandom->Uniform(y,ymax));
  vtx->SetZ(gRandom->Uniform(z,zmax));
  return vtx;
}

void VtxGenerator::SetUniformVtx(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Double_t zmin, Double_t zmax){
  this->x = x;
  this->y = y;
  this->z = z;
  this->xmax = xmax;
  this->ymax = ymax;
  this->zmax = zmax;  
}

Point* VtxGenerator::GetCustomVtx(){
  vtx->SetX(xinput_hist->GetRandom());
  vtx->SetY(yinput_hist->GetRandom());
  vtx->SetZ(zinput_hist->GetRandom());
  return vtx;
}

void VtxGenerator::SetCustomVtx(const char* xinput_file_name,const char* yinput_file_name,const char* zinput_file_name, const char* xinput_hist_name,const char* yinput_hist_name,const char* zinput_hist_name){
  this->xinput_file_name = xinput_file_name;
  this->yinput_file_name = yinput_file_name;
  this->zinput_file_name = zinput_file_name;
  this->xinput_hist_name=xinput_hist_name;   
  this->yinput_hist_name=yinput_hist_name;   
  this->zinput_hist_name=zinput_hist_name;   
  this->xinput_file = new TFile(xinput_file_name);
  this->yinput_file = new TFile(yinput_file_name);
  this->zinput_file = new TFile(zinput_file_name);
  this->xinput_hist = (TH1D*) xinput_file->Get(xinput_hist_name);
  this->yinput_hist = (TH1D*) yinput_file->Get(yinput_hist_name);
  this->zinput_hist = (TH1D*) zinput_file->Get(zinput_hist_name);
  this->xinput_hist->SetDirectory(0);
  this->yinput_hist->SetDirectory(0);
  this->zinput_hist->SetDirectory(0);
  this->xinput_file->Close();
  this->yinput_file->Close();
  this->zinput_file->Close();
  delete xinput_file;
  delete yinput_file;
  delete zinput_file;
  this->used_hist = kTRUE;
}