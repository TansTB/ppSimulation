#include "Reco.h"

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
   L1_candidate=TreeLooper(ptr_L1_hits);
   //Layer 2
   TBranch *b2=input_tree->GetBranch("L2_Hits");
   b2->SetAddress(&ptr_L2_hits);
   L2_candidate=TreeLooper(ptr_L2_hits);
   cout << VertexFinder(L1_candidate, L2_candidate);
}

Reco::~Reco(){ delete input_tree;}

Hit* Reco::TreeLooper(TClonesArray* hits){
   //loop on branches
   for(Int_t i=0;i<input_tree->GetEntries();i++){
     input_tree->GetEvent(i);
     //loop on TClonesArray
     for(Int_t j=0;j<hits->GetEntries();j++){
        Hit *hit=(Hit*)hits->At(j); 
        if(j==0) return hit;
     }
   }
}

Double_t Reco::VertexFinder (Hit * L1_candidate, Hit * L2_candidate){
   return (L1_radius*Cos(L1_candidate->GetPhi())*((L2_candidate->GetZ())-(L1_candidate->GetZ()))/((L1_radius*Cos(L1_candidate->GetPhi()))-(L2_radius*(L2_candidate->GetPhi()))) + L1_candidate->GetZ();
   
}



