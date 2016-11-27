#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include "TFile.h"
#include "TTree.h"
#include "EventGenerator.h"
#include "MyParser.h"
#include "TRandom3.h"
#include "TStopwatch.h"

using namespace std;

int RunManager(char *config_file){
  vector<vector<string> > v;
  ifstream config(config_file);
  cout<<"Reading configuration file..."<<endl;
  ColonParser(config,v);
  delete gRandom;
  gRandom = new TRandom3(stod(v.at(23).at(1)));
  TTree* tree = new TTree("ppSimulation","ppSimulation");
  EventGenerator EG(v,tree);
  cout<<"Creating Output File..."<<endl;
  TFile* output_file = new TFile(v.at(22).at(1).c_str(),"recreate");
  cout<<"Starting simulation.."<<endl;
  TStopwatch* sim_watch = new TStopwatch();
  for(Int_t i=0;i<stod(v.at(21).at(1));i++){
    if(i%100==99) cout <<  i+1 << " Processed events..." << endl;
    EG.NewEvent();
  }
  tree->Write();
  delete tree;
  cout << "Closing Output File: " << output_file->GetName() << endl;
  output_file->Close();
  delete output_file;
  sim_watch->Stop();
  cout << "Simulation completed" << endl;
  sim_watch->Print("u");
  return 0;
}

# ifndef __CINT__
int main(int argc, char *argv[])
{
  if(argc==1)cout << "CONFIG FILE MISSING"<< endl<<"TERMINATING..."<< endl;
  else RunManager(argv[1]);
  return 0;
}
# endif
