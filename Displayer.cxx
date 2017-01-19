#if !defined (__CINT__) || defined(__ROOTCINT__)
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include "Point.h"
#include "Hit.h"
#include "TMath.h"
#include "TPad.h"
#include "TCanvas.h"
#include <algorithm>
#include <vector>
#include <string>
#endif

using namespace std;
using namespace TMath;

//Function to print the resolution histogram
void ResolutionHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    if(input_file->IsZombie()) {
        cout<< "File Not Found! Please check file name"<<endl;
        return;
    }
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Point VTX;
    Point *VTX_ptr=&VTX;
    Double_t RecoVTX_Z;
    Bool_t isReconstructed;
    TBranch *b1=input_tree->GetBranch("Vertex");
    b1->SetAddress(&VTX_ptr);
    TBranch *b2=input_tree->GetBranch("RecoVertexZ");
    b2->SetAddress(&RecoVTX_Z);
    TBranch *b3=input_tree->GetBranch("is_reconstructed");
    b3->SetAddress(&isReconstructed);
    TCanvas *c1 = new TCanvas("c1","Resolution Histogram");
    TH1D *ResHist = new TH1D("Resolution","Resolution;#DeltaZ (cm)",75,-0.25,0.25);
    ResHist->SetDirectory(0);
    for (Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if(isReconstructed)ResHist->Fill(VTX.GetZ()-RecoVTX_Z);
//         cout << VTX.GetZ()<<"\t"<<RecoVTX_Z<<endl;
//         if (((VTX.GetZ()-RecoVTX_Z) < -2)&&isReconstructed) cout << i << endl;
    }
    ResHist->Draw();
    input_file->Close();
    delete input_file;
}

//Function to plot the resolution vs generated Z histogram (best results are obtained if Z is generated with a uniform distribution)
void ResolutionVsGeneratedZHistogram(string input_file_name,Int_t bins){
    TFile *input_file = new TFile(input_file_name.c_str());
    if(input_file->IsZombie()) {
        cout<< "File Not Found! Please check file name"<<endl;
        return;
    }
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Point VTX;
    Point *VTX_ptr=&VTX;
    Double_t RecoVTX_Z;
    Bool_t isReconstructed;
    vector<Double_t>GeneratedZ;
    vector<Double_t>RecoZ;
    TBranch *b1=input_tree->GetBranch("Vertex");
    b1->SetAddress(&VTX_ptr);
    TBranch *b2=input_tree->GetBranch("RecoVertexZ");
    b2->SetAddress(&RecoVTX_Z);
    TBranch *b3=input_tree->GetBranch("is_reconstructed");
    b3->SetAddress(&isReconstructed);
    for (Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if (isReconstructed){
            GeneratedZ.push_back(VTX.GetZ());
            RecoZ.push_back(RecoVTX_Z); 
        }   
    }
    TH1D *ResHist = new TH1D("ResolutionHistogram","Risoluzione",75,-0.25,0.25);
    vector<Double_t>GeneratedZAux(GeneratedZ);
    sort(GeneratedZAux.begin(),GeneratedZAux.end());
    Double_t binsize = (GeneratedZAux.back()-GeneratedZAux.front())/bins;
    TCanvas *c1 = new TCanvas("c1","Resolution Vs Z Histogram");
    TH1D *ResVsZHist = new TH1D("ResolutionVsZHistogram","Resolution vs Generated Z;Z (cm);Resolution (cm)",bins,GeneratedZAux.front(),GeneratedZAux.back());
    ResVsZHist->SetDirectory(0);
    for (Int_t i=1;i<=bins;i++){
            Int_t counter=0;
        for(unsigned j=0;j<GeneratedZ.size();j++){
            if(GeneratedZ.at(j)>=GeneratedZAux.front()+binsize*(i-1) && GeneratedZ.at(j)<GeneratedZAux.front()+binsize*(i)){
                ResHist->Fill(GeneratedZ.at(j)-RecoZ.at(j));
                counter++;
            }
        }
        ResVsZHist->SetBinContent(i,ResHist->GetStdDev());
        ResVsZHist->SetBinError(i,ResHist->GetStdDevError());
        ResHist->Reset();
    }
    ResVsZHist->SetLineColor(kBlack);
    ResVsZHist->SetMarkerStyle(8);
    ResVsZHist->GetYaxis()->SetTitleOffset(1.2);
    gStyle->SetOptStat(0);
    ResVsZHist->Draw("E1 P");
    delete ResHist;
    input_file->Close();    
    delete input_file;
}

//Function to plot the resolution vs generated multiplicity histogram (best results are obtained if the multiplicity is generated with a uniform distribution)
void ResolutionVsMultiplicityHistogram(string input_file_name,Int_t bins){
    TFile *input_file = new TFile(input_file_name.c_str());
    if(input_file->IsZombie()) {
        cout<< "File Not Found! Please check file name"<<endl;
        return;
    }
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Point VTX;
    Point *VTX_ptr=&VTX;
    Double_t RecoVTX_Z;
    Bool_t isReconstructed;
    vector<Double_t>GeneratedZ;
    vector<Double_t>RecoZ;
    Int_t multiplicity;
    vector<Int_t>Multiplicity;
    TBranch *b1=input_tree->GetBranch("Vertex");
    b1->SetAddress(&VTX_ptr);
    TBranch *b2=input_tree->GetBranch("RecoVertexZ");
    b2->SetAddress(&RecoVTX_Z);
    TBranch *b3=input_tree->GetBranch("is_reconstructed");
    b3->SetAddress(&isReconstructed);
    TBranch *b4=input_tree->GetBranch("Multiplicity");
    b4->SetAddress(&multiplicity);
    for (Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if (isReconstructed){
            GeneratedZ.push_back(VTX.GetZ());
            RecoZ.push_back(RecoVTX_Z); 
            Multiplicity.push_back(multiplicity);
        }   
    }
    TH1D *ResHist = new TH1D("ResolutionHistogram","Risoluzione",500,-2,2);
    vector<Int_t> MultiplicityAux(Multiplicity);
    sort(MultiplicityAux.begin(),MultiplicityAux.end());
    Double_t binsize = (MultiplicityAux.back()-MultiplicityAux.front())/bins;
    TCanvas *c1 = new TCanvas("c1","Resolution Vs Multiplicity Histogram");
    TH1D *ResVsZHist = new TH1D("ResolutionVsMultiplicityHistogram","Resolution vs Multiplicity;Multiplicity;Resolution (cm)",bins,MultiplicityAux.front(),MultiplicityAux.back());
    ResVsZHist->SetDirectory(0);
    for (Int_t i=1;i<=bins;i++){
            Int_t counter=0;
        for(unsigned j=0;j<Multiplicity.size();j++){
            if(Multiplicity.at(j)>=MultiplicityAux.front()+binsize*(i-1) && Multiplicity.at(j)<MultiplicityAux.front()+binsize*(i)){
                ResHist->Fill(GeneratedZ.at(j)-RecoZ.at(j));
                counter++;
            }
        }
        cout<<counter<<endl;
        ResVsZHist->SetBinContent(i,ResHist->GetStdDev());
        ResVsZHist->SetBinError(i,ResHist->GetStdDevError());
        ResHist->Reset();
    }
    ResVsZHist->SetLineColor(kBlack);
    ResVsZHist->SetMarkerStyle(8);
    ResVsZHist->GetYaxis()->SetTitleOffset(1.2);
    gStyle->SetOptStat(0);
    ResVsZHist->Draw("E1 P");
    delete ResHist;
    input_file->Close();
    delete input_file;
}

//Function to print the efficiency vs generated multiplicity histogram (must be run on a file created with a custom multiplicity distribution between 0 and 50, giving discrete multiplicities with equal probabilities)
void EfficiencyVsMultiplicityHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    if(input_file->IsZombie()) {
        cout<< "File Not Found! Please check file name"<<endl;
        return;
    }
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Bool_t isReconstructed;
    Int_t multiplicity;
    TBranch *b1=input_tree->GetBranch("is_reconstructed");
    b1->SetAddress(&isReconstructed);
    TBranch *b2=input_tree->GetBranch("Multiplicity");
    b2->SetAddress(&multiplicity);
    TCanvas *c1 = new TCanvas("c1","Efficiency Vs Multiplicity");
    TEfficiency *eff = new TEfficiency("eff","Efficiency Vs Multiplicity;Multiplicity;Efficiency",50,0.5,50.5);
    eff->SetDirectory(0);
    for(Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        eff->Fill(isReconstructed,multiplicity);
    }
    eff->Draw("AP");
    input_file->Close();
    delete input_file;
}


//Function to print the efficiency vs generated multiplicity histogram for particles within 1 sigma(best results are obtained with a uniform multiplicity distribution)
void EfficiencyVsMultiplicityHistogram1Sigma(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    if(input_file->IsZombie()) {
        cout<< "File Not Found! Please check file name"<<endl;
        return;
    }
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Bool_t isReconstructed;
    Int_t multiplicity;
    Point VTX;
    Point *VTX_ptr=&VTX;
    Double_t RecoVTX_Z;
    TBranch *b1=input_tree->GetBranch("is_reconstructed");
    b1->SetAddress(&isReconstructed);
    TBranch *b2=input_tree->GetBranch("Multiplicity");
    b2->SetAddress(&multiplicity);
    TBranch *b3=input_tree->GetBranch("Vertex");
    b3->SetAddress(&VTX_ptr);
    TBranch *b4=input_tree->GetBranch("RecoVertexZ");
    b4->SetAddress(&RecoVTX_Z);    
    TH1D *ResHist = new TH1D("ResolutionHistogram","Risoluzione",500,-2,2);
    TCanvas *c1 = new TCanvas("c1","Efficiency Vs Multiplicity 1 Sigma");
    TEfficiency *eff = new TEfficiency("eff","Efficiency Vs Multiplicity for particles within #sigma;Multiplicity;Efficiency",50,0.5,50.5);
    eff->SetDirectory(0);
    for (Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if(isReconstructed)ResHist->Fill(VTX.GetZ());
    }
    Double_t sigma = ResHist->GetStdDev();
    Double_t mean = ResHist->GetMean();
    delete ResHist;
    for(Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if(TMath::Abs(VTX.GetZ()-mean)<sigma){
            eff->Fill(isReconstructed,multiplicity);
        }
    }
    eff->Draw("AP");
    input_file->Close();
    delete input_file;
}

//Function to print the efficiency vs noise histogram (must be run on a variable noise dataset)
void EfficiencyVsNoiseHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    if(input_file->IsZombie()) {
        cout<< "File Not Found! Please check file name"<<endl;
        return;
    }
    TClonesArray *ptr_L1_hits = new TClonesArray("Hit",400);
    TClonesArray &L1_hits = *ptr_L1_hits;
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Bool_t isReconstructed;
    Int_t multiplicity;
    TBranch *b1=input_tree->GetBranch("is_reconstructed");
    b1->SetAddress(&isReconstructed);
    TBranch *b2=input_tree->GetBranch("Multiplicity");
    b2->SetAddress(&multiplicity);
    TBranch *b3=input_tree->GetBranch("L1_Hits");
    b3->SetAddress(&ptr_L1_hits);
    TCanvas *c1 = new TCanvas("c1","Efficiency Vs Multiplicity");
    TEfficiency *eff = new TEfficiency("eff","Efficiency Vs Multiplicity;Multiplicity;Efficiency",25,0.5,50.5);
    eff->SetDirectory(0);
    for(Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        Int_t noise = 0;
        for(Int_t j=0;j<ptr_L1_hits->GetEntries();j++){
            if(((Hit*)ptr_L1_hits->At(j))->GetLabel()==-1)noise++;
        }
        eff->Fill(isReconstructed,noise);
    }
    eff->Draw("AP");
    input_file->Close();
    delete input_file;
}
