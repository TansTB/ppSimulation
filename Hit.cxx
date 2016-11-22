#include <iostream>
#include "Hit.h"
using namespace std;

Hit::Hit(Double_t label, Double_t phi, Double_t z){
  this->label = label;
  this->phi = phi;
  this->z = z;
  if (this->layer == 1) this->r = 4; //radius in cm
  if (this->layer == 2) this->r = 7; //radius in cm
}

void Hit::SetLabel(Double_t label){this->label = label;}
void Hit::SetPhi(Double_t phi){this->phi = phi;}
void Hit::SetZ(Double_t z){this->z = z;}
