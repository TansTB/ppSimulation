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
    VtxGenerator(unsigned Int_t seed){this->seed = seed;}
    VtxGenerator(const char *input_file_name){this->input_file_name = input_file_name;}
        
    void SetCustomInput(const char* input_file_name, const char* hist_name);
    void SetSeed(unsigned Int_t seed){this->seed = seed;}
    unsigned Int_t GetSeed(){return seed;}
    char* GetInputFileName(){return input_file_name;}
    
    Point* GetGausVtx(Double_t x, Double_t sx, Double_t y, Double_t sy, Double_t z, Double_t sz);
    Point* GetUniformVtx(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, Double_t zmin, Double_t zmax);
    Point* GetCustomVtx();

  private:
    const char *input_file_name;
    const char *hist_name;
    TFile *input_file;
    TH1D *input_hist;
    unsigned Int_t seed;
};
#endif