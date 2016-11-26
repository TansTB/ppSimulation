#include <iostream>
#include "Hit.h"
#include "TMath.h"
using namespace std;
using namespace TMath;

Hit::Hit(Int_t label, Double_t phi, Double_t z){
  this->label = label;
  this->phi = phi;
  this->z = z;
}

void Hit::SetLabel(Int_t label){this->label = label;}
void Hit::SetPhi(Double_t phi){
  while(phi>2*Pi())phi-=2*Pi();
  this->phi = phi;
  
}
void Hit::SetZ(Double_t z){this->z = z;}

