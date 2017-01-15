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
   this->L1_radius = 4.;    //test mode
   this->L2_radius = 7.;    //test mode
   
   //new tree branches
   TBranch *newBranch = oldtree->Branch("RecoVertexZ",&vertex_z);
   TBranch *newBranch2 = oldtree->Branch("is_reconstructed",&is_reconstructed);
   
   //read tree
   this->input_tree = oldtree;
   TBranch *b1=input_tree->GetBranch("L1_Hits");
   b1->SetAddress(&ptr_L1_hits);
   TBranch *b2=input_tree->GetBranch("L2_Hits");
   b2->SetAddress(&ptr_L2_hits);
   
   //delta_phi calculation
   this->delta_phi = DeltaPhiSampling();

   //loop on events 
   for(Int_t i=0;i<input_tree->GetEntries();i++){
      input_tree->GetEvent(i);
      
      //vertex is calculated for event i
      GetEventVertex();
      //if (i<50) cout << endl <<"Check. For event " << i << " the vertex for this event is " << vertex_z << " is reconstructed? " << is_reconstructed << endl;

      //fill new branches
      if (is_reconstructed == kTRUE) newBranch->Fill();
      newBranch2->Fill(); 
   }
   oldtree->Write("ppSimulation",TObject::kOverwrite);
   oldfile -> Close();
}

Reco::~Reco(){ delete input_tree;}

void Reco::GetEventVertex(){

   //loop on L1 TClonesArray
   for(Int_t j=0;j<ptr_L1_hits->GetEntries();j++){ 
   L1_candidate = (Hit*)ptr_L1_hits->At(j);

      //loop on L2 TClonesArray
      for(Int_t k=0;k<ptr_L2_hits->GetEntries();k++){
         L2_candidate=(Hit*)ptr_L2_hits->At(k);

         // hit match 
         if (Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi()) <= Pi()) dif = Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi());
         else dif = 2*Pi() - Abs(L2_candidate->GetPhi() - L1_candidate->GetPhi());
         if (dif <= delta_phi){ 
           intersection = GetIntersection(L1_candidate,L2_candidate);
           intersection_list[counter] = intersection; 
           counter++;
           vertex_candidates->Fill(intersection);
         }
         
      }     
     
   }

   //find maximum bin, maximum bin boundaries, second and third maximum bins
   //highest bin
   binmax = vertex_candidates->GetMaximumBin();    
   my_bin_content = 0;
   my_bin_content = vertex_candidates->GetBinContent(binmax); 
   z_min = vertex_candidates->GetBinLowEdge(binmax);
   z_max = vertex_candidates->GetBinLowEdge(binmax+1);
   //left highest bin
   vertex_candidates->GetXaxis()->SetRange(0,binmax-1);  
   low_bin_content = vertex_candidates->GetBinContent(vertex_candidates->GetMaximumBin());
   //right highest bin 
   vertex_candidates->GetXaxis()->SetRange(binmax+1,149);
   high_bin_content = vertex_candidates->GetBinContent(vertex_candidates->GetMaximumBin());
   //set range back to original size  
   vertex_candidates->GetXaxis()->SetRange(0,149);                                        
   z_sum = 0;
   bin_entries = 0;
   
   //condition to validate reconstruction ( maximum bin entries > 1.5 * second maximum bin entries)

   //reconstructed events
   if (my_bin_content > 1.5*max(low_bin_content,high_bin_content)){
     is_reconstructed = kTRUE;
     //get highest bin z entries sum
     for (Int_t k = 0; k<=counter; k++){
       if(intersection_list[k] >= z_min && intersection_list[k] <= z_max){ 
       z_sum += intersection_list[k];
       bin_entries++;      
       }     
     }
     //vertex_candidates->DrawCopy();
     counter = 0;
     vertex_candidates->Reset();     //rest z candidates histogram
     vertex_z = z_sum / (bin_entries);   //return vertex z average  
   }

   //not recostructed events
   else {
     is_reconstructed = kFALSE;
     counter = 0;                   
     vertex_candidates->Reset();    //rest z candidates histogram
   }	
}

Double_t Reco::GetIntersection(Hit * L1_candidate, Hit * L2_candidate){
   return (L1_radius*Cos(L1_candidate->GetPhi())*(L2_candidate->GetZ()-L1_candidate->GetZ()))/(L1_radius*Cos(L1_candidate->GetPhi())-L2_radius*Cos(L2_candidate->GetPhi())) + L1_candidate->GetZ();   
}


string Reco::RemoveWhitespaces(string& s){
  s.erase(std::remove_if(s.begin(),s.end(),[](char c){return std::isspace(static_cast<unsigned char>(c));}),s.end());
  return s;
}


Double_t Reco::DeltaPhiSampling(){
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

   //delta_phi_distribution->DrawCopy();   test mode
   return delta_phi_distribution->GetRMS(1);
}

