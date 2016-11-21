#include "Track.h"
#include <TMath.h>

using namespace TMath;
using namespace std;

Track::Track(Double_t theta, Double_t phi){
   this->theta = theta;
   this->phi = phi;
   this->SetComp();
}

void Track::SetTheta(Double_t theta){this->theta = theta;}

void Track::SetPhi(Double_t phi){this->phi = phi;}

void Track::SetComp(){
   comp[0]= Sin(theta)*Cos(phi);
   comp[1]= Sin(theta)*Sin(phi);
   comp[2]= Cos(theta);
}

void Track::Print(){
   cout << "*********************************************************" << endl;
   cout << "Theta       " << Track::GetTheta() << endl <<"Phi         " << Track::GetPhi() << endl << "Componenti "; 
   for (Int_t i=0; i<3; i++) {cout << comp[i] << "  ";}
   cout << endl << "*********************************************************" << endl;
}

void Track::Rotate(Double_t theta_p, Double_t phi_p){

   //matrix
   Double_t mr[3][3];                        
   mr[0][0]= -Sin(phi);
   mr[1][0]= Cos(phi);
   mr[2][0]= 0.;
   mr[0][1]= -Cos(phi)*Cos(theta);
   mr[1][1]= -Cos(theta)*Sin(phi);
   mr[2][1]= Sin(theta);
   mr[0][2]= Sin(theta)*Cos(phi);
   mr[1][2]= Sin(theta)*Sin(phi);
   mr[2][2]= Cos(theta);

   //component update
   Double_t comp_p[3]; 
   comp_p[0]=Sin(theta_p)*Cos(phi_p);
   comp_p[1]=Sin(theta_p)*Sin(phi_p);
   comp_p[2]=Cos(theta_p);

   for(Int_t i=0;i<3;i++){
      comp[i]=0.;
      for(Int_t j=0;j<3;j++){
         comp[i]+=mr[i][j]*comp_p[j];
      }
   }

   // angle update (theta)
   Double_t theta_sum = theta + theta_p;
   if (theta_sum >= Pi()) theta_sum -= Pi();
   Track::SetTheta(theta_sum);

   //angle update (phi)
   Double_t phi_sum = phi + phi_p;
   if (phi_sum >= 2*Pi()) phi_sum -= 2*Pi();
   Track::SetPhi(phi_sum);
}


