#include "Reco.h"
#include "Hit.cxx"

using namespace std;
using namespace TMath;

//Official constructor
//Reco::Reco(TTree *input_tree, vector<vector<string> > configs){
//this->input_tree = input_tree;

//Unofficial constructor used for debugging///////////////////////////////////////////////////////
   Reco::Reco(Double_t delta_phi){ 
   this->delta_phi=delta_phi;
   //Apertura file di input
   TFile *input_file = new TFile("FirstSimulation.root");
   //Lettura TTree  e branch
   this->input_tree = (TTree*)input_file->Get("ppSimulation");
//end of unofficial part of the constructor///////////////////////////////////////////////////////
     

   //read input tree
   //input_tree->SetBranchAddress("Multiplicity", &multiplicity);
   TBranch *b1=input_tree->GetBranch("L1_Hits");
   b1->SetAddress(&ptr_L1_hits);
   TBranch *b2=input_tree->GetBranch("L2_Hits");
   b2->SetAddress(&ptr_L2_hits);
   
   //loop on events
   for(Int_t i=0;i<input_tree->GetEntries();i++){
      input_tree->GetEvent(i);
      //get vertex distribution 
      vertex_distribution->Fill(GetEventVertex());
   }
   vertex_distribution->DrawCopy();
   
   //cout << multiplicity;
}
Reco::~Reco(){ delete input_tree;}

Double_t Reco::GetEventVertex(){
   //loop on L1 TClonesArray
   for(Int_t j=0;j<ptr_L1_hits->GetEntries();j++){ 
   L1_candidate = (Hit*)ptr_L1_hits->At(j);

      //loop on L2 TClonesArray
      for(Int_t k=0;k<ptr_L2_hits->GetEntries();k++){
         L2_candidate=(Hit*)ptr_L2_hits->At(k);

         // hit match 
         if (Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi()) <= delta_phi){
         //comp[j][k] = GetIntersection(L1_candidate,L2_candidate);
         vertex_candidates->Fill(GetIntersection(L1_candidate,L2_candidate));
         }

         // no hit match
         //comp[j][k]=40;
      }
   } 
   //get histogram maximum bin
   binmax = vertex_candidates->GetMaximumBin();
   return vertex_candidates->GetXaxis()->GetBinCenter(binmax);
   //vertex_candidates->DrawCopy();
}

Double_t Reco::GetIntersection(Hit * L1_candidate, Hit * L2_candidate){
   return (L1_radius*Cos(L1_candidate->GetPhi())*(L2_candidate->GetZ()-L1_candidate->GetZ()))/(L1_radius*Cos(L1_candidate->GetPhi())-L2_radius*Cos(L2_candidate->GetPhi())) + L1_candidate->GetZ();
   
}






