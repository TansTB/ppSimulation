#ifndef HIT_H
#define HIT_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include "TObject.h"
#endif

class Hit:public TObject{
public:
  Hit(){}
  Hit(Int_t label, Double_t phi, Double_t z);
  
  void SetLabel(Int_t label);
  void SetPhi(Double_t phi);
  void SetZ(Double_t z);
  Int_t GetLabel(){return label;}
  Double_t GetPhi(){return phi;}
  Double_t GetZ(){return z;}
  
private:
  Int_t label;
  Double_t phi;
  Double_t z;
};
#endif
