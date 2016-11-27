#include "Reco.h"
#include "Hit.cxx"

using namespace std;
using namespace TMath;

//Reco::Reco(TTree *input_tree, vector<vector<string> > configs){

   //this->input_tree = input_tree;

////////////////////////////////TEST CODE//////////////////////////////////
//________________________________________________________________________
   Reco::Reco(Double_t delta_phi){ 
   //Apertura file di input
   TFile *input_file = new TFile("test.root");
   //Lettura TTree  e branch
   this->input_tree = (TTree*)input_file->Get("T");
//________________________________________________________________________

   //Layer 1
   TBranch *b1=input_tree->GetBranch("L1_Hits");
   b1->SetAddress(&ptr_L1_hits);
   Hit * test1 = new Hit::Hit(1,Pi(),1);
   Hit * test2= new Hit(1,0.5*Pi(),2);
   //Layer 2
   TBranch *b2=input_tree->GetBranch("L2_Hits");
   b2->SetAddress(&ptr_L2_hits);
   cout << VertexFinder(test1,test2);
}

Reco::~Reco(){ delete input_tree;}

void Reco::TreeLooper(){
   //loop on branches
   for(Int_t i=0;i<input_tree->GetEntries();i++){
     input_tree->GetEvent(i);
     //loop on L1 TClonesArray
     for(Int_t j=0;j<ptr_L1_hits->GetEntries();j++){ 
        L1_candidate = (Hit*)ptr_L1_hits->At(j);
        //loop on L2 TClonesArray
        for(Int_t k=0;j<ptr_L2_hits->GetEntries();k++){
            Hit *hit=(Hit*)ptr_L2_hits->At(k);
            if ((Abs(hit->GetPhi() - L1_candidate->GetPhi()) <= delta_phi)) L2_candidate = hit;
        }
     }
   }
} 

Double_t Reco::VertexFinder (Hit * L1_candidate, Hit * L2_candidate){
   return (L1_radius*Cos(L1_candidate->GetPhi())*(L2_candidate->GetZ()-L1_candidate->GetZ()))/(L1_radius*Cos(L1_candidate->GetPhi())-L2_radius*Cos(L2_candidate->GetPhi())) + L1_candidate->GetZ();
   
}




