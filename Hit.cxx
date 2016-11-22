#include <iostream>
#include "Hit.h"
#include "TMath.h"
using namespace std;
using namespace TMath;

Hit::Hit(Double_t label, Double_t phi, Double_t z, Int_t layer){
  this->label = label;
  this->phi = phi;
  this->z = z;
  Hit::SetLayer(layer);
}

void Hit::SetLabel(Double_t label){this->label = label;}
void Hit::SetPhi(Double_t phi){this->phi = phi;}
void Hit::SetZ(Double_t z){this->z = z;}
void Hit::SetLayer(Double_t layer){
  this->layer = layer;
  if (layer == 1) r = 4; //radius in cm
  if (layer == 2) r = 7; //radius in cm
}
