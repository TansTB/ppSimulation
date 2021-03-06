#ifndef POINT_H
#define POINT_H
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include "TObject.h"
#endif

class Point:public TObject{
public:
  Point(){}
  Point(Double_t x, Double_t y, Double_t z);
  
  void SetX(Double_t x);
  void SetY(Double_t y);
  void SetZ(Double_t z);
//   void Print();
  Double_t GetX(){return x;}
  Double_t GetY(){return y;}
  Double_t GetZ(){return z;}
  
private:
  Double_t x;
  Double_t y;
  Double_t z;
  
ClassDef(Point,1);
};
#endif
