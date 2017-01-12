#include "Reco.h"

using namespace std;
using namespace TMath;

//Reco::Reco(TTree *input_tree, vector<vector<string> > configs){ not in test mode 
Reco::Reco(Int_t t){ 

   //test mode (opens tree from file)
   TFile *oldfile = new TFile("FirstSimulation.root","UPDATE");
   TTree *oldtree = (TTree*)oldfile->Get("ppSimulation");

   //configuration
   //this->L1_radius = stod(configs.at(28).at(1));  not in test mode
   //this->L2_radius = stod(configs.at(32).at(1));  not in test mode
   //this->delta_phi = stod(configs.at(38).at(1));  not in test mode
   this->delta_phi = 0.0018;   //to discuss 0.0001
   this->L1_radius = 4.;
   this->L2_radius = 7.;

   //read input tree
   this->input_tree = oldtree;
   TBranch *b1=input_tree->GetBranch("L1_Hits");
   b1->SetAddress(&ptr_L1_hits);
   TBranch *b2=input_tree->GetBranch("L2_Hits");
   b2->SetAddress(&ptr_L2_hits);
   //DeltaPhiSampling();
   
   //loop on events 
   for(Int_t i=0;i<input_tree->GetEntries();i++){
      input_tree->GetEvent(i);

      //get average final vertex and final vertex distribution
      if (i==1) {GetEventVertex();  
      vertex_distribution->Fill(GetEventVertex());}
   }
   //this->vertex_z /= input_tree->GetEntries(); 
   //vertex_distribution->DrawCopy(); 
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
         if (Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi()) <= Pi()) dif = Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi());
         else dif = 2*Pi() - Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi());
         if (dif <= delta_phi) vertex_candidates->Fill(GetIntersection(L1_candidate,L2_candidate)); 
       }     
      
   }
 
   //get histogram maximum bin
   binmax = vertex_candidates->GetMaximumBin();
   vertex_candidates->DrawCopy();
   return vertex_candidates->GetXaxis()->GetBinCenter(binmax); 
}

Double_t Reco::GetIntersection(Hit * L1_candidate, Hit * L2_candidate){
   return (L1_radius*Cos(L1_candidate->GetPhi())*(L2_candidate->GetZ()-L1_candidate->GetZ()))/(L1_radius*Cos(L1_candidate->GetPhi())-L2_radius*Cos(L2_candidate->GetPhi())) + L1_candidate->GetZ();
   
}


string Reco::RemoveWhitespaces(string& s){
  s.erase(std::remove_if(s.begin(),s.end(),[](char c){return std::isspace(static_cast<unsigned char>(c));}),s.end());
  return s;
}


void Reco::DeltaPhiSampling(){
   //loop on events
   for(Int_t i=0;i<input_tree->GetEntries();i++){
      input_tree->GetEvent(i);   

      //loop on L1 TClonesArray
      for(Int_t j=0;j<ptr_L1_hits->GetEntries();j++){ 
      L1_candidate = (Hit*)ptr_L1_hits->At(j);

         //loop on L2 TClonesArray
         for(Int_t k=0;k<ptr_L2_hits->GetEntries();k++){
         L2_candidate=(Hit*)ptr_L2_hits->At(k);

         // hit match 
         if ((L2_candidate->GetLabel() == L1_candidate->GetLabel()) && L2_candidate->GetLabel() != -1){
             if ((L2_candidate->GetPhi() - L1_candidate->GetPhi() < Pi())&& (L2_candidate->GetPhi() - L1_candidate->GetPhi() > -Pi() ) ) delta_phi_distribution->Fill(L2_candidate->GetPhi() - L1_candidate->GetPhi());
             if (L2_candidate->GetPhi() - L1_candidate->GetPhi() > Pi()) delta_phi_distribution->Fill(2*Pi()-(L2_candidate->GetPhi() - L1_candidate->GetPhi())); 
             if (L2_candidate->GetPhi() - L1_candidate->GetPhi() < -Pi()) delta_phi_distribution->Fill(-2*Pi()+(L2_candidate->GetPhi() - L1_candidate->GetPhi())); 
         }        
 }   
      }
    }
   delta_phi_distribution->DrawCopy();
}

