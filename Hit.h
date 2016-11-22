#ifndef HIT_H
#define HIT_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include "TObject.h"
#endif

class Hit:public TObject{
public:
  Hit(){}
  Hit(Double_t label, Double_t phi, Double_t z, Int_t layer);
  
  void SetLabel(Double_t label);
  void SetPhi(Double_t phi);
  void SetZ(Double_t z);
  void SetLayer(Double_t layer);
  Double_t GetLabel(){return label;}
  Double_t GetPhi(){return phi;}
  Double_t GetZ(){return z;}
  Int_t GetLayer(){return layer;}
  
private:
  Double_t label;
  Double_t phi;
  Double_t z;
  Double_t r;
  Int_t layer; // layer 1 or layer 2 (from the centre)
};
#endif
