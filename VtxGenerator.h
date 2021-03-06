#ifndef VTXGENERATOR_H
#define VTXGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Point.h"
#include "TFile.h"
#include "TH1D.h"
#include "TRandom3.h"
#endif

class VtxGenerator{
public:
  VtxGenerator(){this->vtx = new Point();}
  VtxGenerator(const char* xinput_file_name,const char* yinput_file_name,const char* zinput_file_name, const char* xinput_hist_name,const char* yinput_hist_name,const char* zinput_hist_name);
  ~VtxGenerator();
  
  const char* GetXInputFileName(){return xinput_file_name;}
  const char* GetYInputFileName(){return yinput_file_name;}
  const char* GetZInputFileName(){return zinput_file_name;}
  const char* GetXInputHistName(){return xinput_hist_name;}
  const char* GetYInputHistName(){return yinput_hist_name;}
  const char* GetZInputHistName(){return zinput_hist_name;}
  Point* GetConstVtx();
  void SetConstVtx(Double_t x, Double_t y, Double_t z);  
  Point* GetGausVtx();
  void SetGausVtx(Double_t x, Double_t sx, Double_t y, Double_t sy, Double_t z, Double_t sz);
  Point* GetUniformVtx();
  void SetUniformVtx(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Double_t zmin, Double_t zmax);
  Point* GetCustomVtx();
  void SetCustomVtx(const char* xinput_file_name,const char* yinput_file_name,const char* zinput_file_name,const char* xinput_hist_name,const char* yinput_hist_name,const char* zinput_hist_name);
  
private:
  VtxGenerator(const VtxGenerator &other);
  VtxGenerator& operator=(const VtxGenerator& other);
  
  Point *vtx;
  const char *xinput_file_name;
  const char *xinput_hist_name;
  const char *yinput_file_name;
  const char *yinput_hist_name;
  const char *zinput_file_name;
  const char *zinput_hist_name;
  TFile *xinput_file;
  TFile *yinput_file;
  TFile *zinput_file;
  TH1D *xinput_hist;
  TH1D *yinput_hist;
  TH1D *zinput_hist;
  Bool_t used_hist=0;
  Double_t x,y,z,sx,sy,sz,xmax,ymax,zmax;
  
};
#endif
