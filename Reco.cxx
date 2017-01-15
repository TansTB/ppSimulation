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
   this->L1_radius = 4.;
   this->L2_radius = 7.;
   
   TBranch *newBranch = oldtree->Branch("RecoVertexZ",&vertex_z, "vertex_z/F");
   TBranch *newBranch2 = oldtree->Branch("is_reconstructed",&is_reconstructed, "is_reconstructed/F");
   

   //read input tree
   this->input_tree = oldtree;
   TBranch *b1=input_tree->GetBranch("L1_Hits");
   b1->SetAddress(&ptr_L1_hits);
   TBranch *b2=input_tree->GetBranch("L2_Hits");
   b2->SetAddress(&ptr_L2_hits);
   
  
   //delta_phi calculation
   this->delta_phi = DeltaPhiSampling();
   cout << endl << "delta_phi is " << delta_phi << endl;    //just in test mode

   //loop on events 
   for(Int_t i=0;i<input_tree->GetEntries();i++){
      input_tree->GetEvent(i);
      vertex_z = GetEventVertex();
      //cout << endl << " vertice " <<  << endl;
      newBranch->Fill();
      newBranch2->Fill();

      //for single event plot histogram of Z vertex candidates
      //if (i==1) cout << endl << " vertex is " << GetEventVertex() <<endl;  
   }
   //oldfile -> Close();

   oldtree->Write();
   //oldfile -> Close();
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
         if (dif <= delta_phi){ 
           intersection = GetIntersection(L1_candidate,L2_candidate);
           intersection_list[counter] = intersection; 
           counter++;
           vertex_candidates->Fill(intersection);
           //vertex_candidates->Fill(GetIntersection(L1_candidate,L2_candidate)); 
         }
         
      }     
     
   }
   //z intersection array
   //sort(begin(intersection_list),end(intersection_list));
   //for (Int_t a = 0; a<counter; a++){
   //cout << " z check " << intersection_list[a] << endl;
   // }
    
   //get histogram maximum bin
   binmax = vertex_candidates->GetMaximumBin();    //selected z bin number
   my_bin_content = 0;
   my_bin_content = vertex_candidates->GetBinContent(binmax); //selected z entries
   vertex_candidates->GetXaxis()->SetRange(0,binmax-1);  
   low_bin_content = vertex_candidates->GetBinContent(vertex_candidates->GetMaximumBin()); //left highest bin entries
   vertex_candidates->GetXaxis()->SetRange(binmax+1,149);
   high_bin_content = vertex_candidates->GetBinContent(vertex_candidates->GetMaximumBin());  //right highest bin entries
   vertex_candidates->GetXaxis()->SetRange(0,149);                                           //set range back to original size
   z_min = vertex_candidates->GetBinLowEdge(binmax);
   //cout << " z min " << z_min;
   z_max = vertex_candidates->GetBinLowEdge(binmax+1);
   z_sum = 0;
   bin_entries = 0;
   
   //condition to validate reconstruction
   //cout << "max" << endl << my_bin_content << endl;
   //Double_t my_second_bin_content = 1.5*max(low_bin_content,high_bin_content);
   //cout << endl << " my second bin content is " << my_second_bin_content << " my bin content is " << my_bin_content << endl;
   //cout << endl << " my bin content is " << my_bin_content << endl;
   if (my_bin_content > 1.5*max(low_bin_content,high_bin_content)){
   //if (my_bin_content > 7){
     is_reconstructed = 1;
     cout << endl << "kTrue" << endl; 
     for (Int_t k = 0; k<=counter; k++){
       if(intersection_list[k] >= z_min && intersection_list[k] <= z_max){ 
       z_sum += intersection_list[k];
       bin_entries++;      
       }     
     }
   //cout << endl << "bin entries is " << bin_entries << "z sum is " << z_sum << endl;
   //vertex_candidates->DrawCopy();
     counter = 0;
     vertex_candidates->Reset();
     return z_sum / (bin_entries);
     
   }
   else {
     is_reconstructed = 0;
     cout << endl << "kFalse" << endl;
     counter = 0;
     vertex_candidates->Reset();
     return 99;
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
   //delta_phi_distribution->DrawCopy();   just here as a check, to delete in final version
   return delta_phi_distribution->GetRMS(1);
}

