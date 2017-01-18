#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TStopwatch.h"
#include "EventGenerator.h"
#include "Reco.h"
#include "MyParser.h"

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
//     cout << "Event " << i<< endl;
    EG.NewEvent();  
    if(i%1000==999) cout <<  i+1 << " generated events..." << endl;
  }
  sim_watch->Stop();
  cout << "Simulation completed" << endl;
  cout << "Starting reconstruction.." << endl;
  TStopwatch* reco_watch = new TStopwatch();
  Reco Reconstruction(v,tree);
  reco_watch->Stop();
  tree->Write();
  delete tree;
  cout << "Closing Output File: " << output_file->GetName() << endl;
  output_file->Close();
  cout << "Reconstruction completed" << endl;
  cout << "************SIMULATION PERFORMANCE************" <<endl;
  sim_watch->Print("u");
  cout << "**********RECONSTRUCTION PERFORMANCE**********" <<endl;
  reco_watch->Print("u");
  delete output_file;
  delete sim_watch;
  delete reco_watch;
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
