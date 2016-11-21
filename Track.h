#ifndef TRACK_H
#define TRACK_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TObject.h"
#endif

class Track:public TObject{
public:
  Track(){}
  Track(Double_t theta, Double_t phi);
  
  void SetTheta(Double_t theta);
  void SetPhi(Double_t phi);
  void SetComp();
  void Rotate(Double_t theta_p, Double_t phi_p); //rotates track with given angles, updates components and angles (sum of original and new angles)
  Double_t GetTheta(){return theta;}
  Double_t GetPhi(){return phi;}
  Double_t * GetComp(){return comp;}
  void Print();
  
private:
  Double_t theta;
  Double_t phi;
  Double_t comp[3];
};
#endif
