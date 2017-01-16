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
#include <algorithm>
#include <vector>
#include <string>
#endif

using namespace std;
using namespace TMath;

//Function to print the resolution histogram
void ResolutionHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    input_tree->Draw("z-RecoVertexZ","is_reconstructed");
    TH1F *ResHist = (TH1F*)gPad->GetPrimitive("htemp");
    input_file->Close();
}

//Function to print the resolution vs generated Z histogram (must be run on a file created with a custom vertex distribution between -16 and 16, giving discrete verteces with equal probabilities)
void ResolutionVsGeneratedZHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Point VTX;
    Point *VTX_ptr = &VTX;
    Double_t RecoVTX_Z;
    Double_t *RecoVTX_Z_ptr = &RecoVTX_Z;
    Bool_t isReconstructed=0;
    Bool_t *isReconstructed_ptr = &isReconstructed;
    vector<Double_t>GeneratedZ;
    vector<Double_t>RecoZ;
    Double_t errors[33];
    TH1D *ResVsZHist = new TH1D("ResolutionVsZHistogram","Risoluzione vs Z generata;Z (cm);Risoluzione (cm)",33,-16.5,16.5);
    TBranch *b1=input_tree->GetBranch("Vertex");
    b1->SetAddress(&VTX_ptr);
    TBranch *b2=input_tree->GetBranch("RecoVertexZ");
    b2->SetAddress(&RecoVTX_Z_ptr);
    TBranch *b3=input_tree->GetBranch("is_reconstructed");
    b3->SetAddress(&isReconstructed_ptr);
    for (Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if (isReconstructed) {
            GeneratedZ.push_back(VTX.GetZ());
            RecoZ.push_back(RecoVTX_Z); 
        }
    }
    TH1D *ResHist = new TH1D("ResolutionHistogram","Risoluzione",100,-20,20);
    vector<Double_t>GeneratedZAux(GeneratedZ);
    vector<Double_t>GeneratedZToSearch;
    sort(GeneratedZAux.begin(),GeneratedZAux.end());
    GeneratedZToSearch.push_back(GeneratedZAux.at(0));
    for(Double_t i : GeneratedZAux) if(i>GeneratedZToSearch.back())GeneratedZToSearch.push_back(i);
    for(Double_t i : GeneratedZToSearch){
        for(Int_t j;j<GeneratedZ.size();j++){
            if(GeneratedZ.at(j)==i)ResHist->Fill(GeneratedZ.at(j)-RecoZ.at(j));
        }
        ResVsZHist->Fill(i,ResHist->GetStdDev());
        ResVsZHist->SetBinError((int)(i+16.5),ResHist->GetStdDevError());
        ResHist->Reset();
    }
    ResVsZHist->DrawCopy();
    input_file->Close();
}

//Function to print the resolution vs generated multiplicity histogram (must be run on a file created with a custom multiplicity distribution between 0 and 50, giving discrete multiplicities with equal probabilities)
void ResolutionVsMultiplicityHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Point VTX;
    Point *VTX_ptr = &VTX;
    Double_t RecoVTX_Z;
    Double_t *RecoVTX_Z_ptr = &RecoVTX_Z;
    Bool_t isReconstructed=0;
    Bool_t *isReconstructed_ptr = &isReconstructed;
    Int_t multiplicity;
    Int_t *multiplicity_ptr = &multiplicity;
    vector<Double_t>GeneratedZ;
    vector<Double_t>RecoZ;
    vector<Int_t>Multiplicity;
    TH1D *ResVsMultHist = new TH1D("MultiplicityVsZHistogram","Risoluzione Vs Molteplicità;Molteplicità;Risoluzione (cm)",51,-0.5,50.5);
    TBranch *b1=input_tree->GetBranch("Vertex");
    b1->SetAddress(&VTX_ptr);
    TBranch *b2=input_tree->GetBranch("RecoVertexZ");
    b2->SetAddress(&RecoVTX_Z_ptr);
    TBranch *b3=input_tree->GetBranch("is_reconstructed");
    b2->SetAddress(&isReconstructed_ptr);
    TBranch *b4=input_tree->GetBranch("Multiplicity");
    b4->SetAddress(&multiplicity_ptr);
    for (Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if (isReconstructed) {
            GeneratedZ.push_back(VTX.GetZ());
            RecoZ.push_back(RecoVTX_Z);
            Multiplicity.push_back(multiplicity);
        }
    }
    TH1D *ResHist = new TH1D("ResolutionHistogram","Risoluzione",100,-20,20);
    vector<Int_t>MultiplicityAux(Multiplicity);
    vector<Int_t>MultiplicityToSearch;
    sort(MultiplicityAux.begin(),MultiplicityAux.end());
    MultiplicityToSearch.push_back(MultiplicityAux.at(0));
    for(Int_t i : MultiplicityAux) if(i>MultiplicityToSearch.back())MultiplicityToSearch.push_back(i);
    for(Int_t i : MultiplicityToSearch){
        for(Int_t j;j<Multiplicity.size();j++){
            if(Multiplicity.at(j)==i)ResHist->Fill(GeneratedZ.at(j)-RecoZ.at(j));
        }
        ResVsMultHist->Fill(i,ResHist->GetStdDev());
        ResVsMultHist->SetBinError((int)(i),ResHist->GetStdDevError());
        ResHist->Reset();
    }
    ResVsMultHist->DrawCopy();
    input_file->Close();
}

//Function to print the efficiency vs generated multiplicity histogram (must be run on a file created with a custom multiplicity distribution between 0 and 50, giving discrete multiplicities with equal probabilities)
void EfficiencyVsMultiplicityHistogram(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Bool_t isReconstructed=0;
    Bool_t *isReconstructed_ptr = &isReconstructed;
    Int_t multiplicity;
    Int_t *multiplicity_ptr = &multiplicity;
    TBranch *b1=input_tree->GetBranch("is_reconstructed");
    b1->SetAddress(&isReconstructed_ptr);
    TBranch *b2=input_tree->GetBranch("Multiplicity");
    b2->SetAddress(&multiplicity_ptr);
    TEfficiency *eff = new TEfficiency("eff","Efficienza Vs Molteplicità;Molteplicità;Efficienza",50,0.5,50.5);
    for(Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        eff->Fill(isReconstructed,multiplicity);
    }
    input_file->Close();
    eff->Draw("AP");
}

//Function to print the efficiency vs generated multiplicity histogram for vertices beneath one sigma (must be run on a file created with a custom multiplicity distribution between 0 and 50, giving discrete multiplicities with equal probabilities)
void EfficiencyVsMultiplicityHistogram1sigma(string input_file_name){
    TFile *input_file = new TFile(input_file_name.c_str());
    TTree *input_tree = (TTree*)input_file->Get("ppSimulation");
    Bool_t isReconstructed=0;
    Bool_t *isReconstructed_ptr = &isReconstructed;
    Int_t multiplicity;
    Int_t *multiplicity_ptr = &multiplicity;
    Point VTX;
    Point *VTX_ptr = &VTX;
    TBranch *b1=input_tree->GetBranch("is_reconstructed");
    b1->SetAddress(&isReconstructed_ptr);
    TBranch *b2=input_tree->GetBranch("Multiplicity");
    b2->SetAddress(&multiplicity_ptr);
    TBranch *b3=input_tree->GetBranch("Vertex");
    b3->SetAddress(&VTX_ptr);
    TEfficiency *eff = new TEfficiency("eff","Efficienza Vs Molteplicità per particelle generate entro 1 Sigma;Molteplicità;Efficienza",50,0.5,50.5);
    for(Int_t i=0;i<input_tree->GetEntries();i++){
        input_tree->GetEvent(i);
        if(Abs((VTX.GetZ())<5.3)&&(Abs(VTX.GetY())<0.01)&&(Abs(VTX.GetX())<0.01))eff->Fill(isReconstructed,multiplicity);
    }
    input_file->Close();
    eff->Draw("AP");
}
