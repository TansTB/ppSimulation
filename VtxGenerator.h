#ifndef VTXGENERATOR_H
#define VTXGENERATOR_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Point.h"
#include "TRandom3.h"
#include "TFile.h"
#endif

class VtxGenerator{
  public:
    VtxGenerator(){}
    VtxGenerator(const char *input_file_name, const char* input_hist_name);
    ~VtxGenerator();
        
    void SetCustomInput(const char* input_file_name, const char* input_hist_name);
    const char* GetInputFileName(){return input_file_name;}
    const char* GetInputHistName(){return input_hist_name;}
    Point* GetGausVtx(Double_t x, Double_t sx, Double_t y, Double_t sy, Double_t z, Double_t sz);
    Point* GetUniformVtx(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Double_t zmin, Double_t zmax);
    Point* GetCustomVtx();

  private:
    const char *input_file_name;
    const char *input_hist_name;
    TFile *input_file;
    TH1D *input_hist;
    Bool_t used_hist=0;
};
#endif