#include "EventGenerator"

using namespace std;

EventGenerator::EventGenerator(vector<vector<strings> > configs,TTree *tree){
  //Generator Configuration
  this->tree = tree;
  if(RemoveWhitespaces(configs.at(0).at(1))=="constant"){
    vtx_gen_mode=0;
    vtx_gen.SetConstVtx(stod(configs.at(1).at(1)),stod(configs.at(1).at(2)),stod(configs.at(1).at(3)));
  }
  if(RemoveWhitespaces(configs.at(0).at(1))=="gaussian"){
    vtx_gen_mode=1;
    vtx_gen.SetGausVtx(stod(configs.at(2).at(1)),stod(configs.at(2).at(2)),stod(configs.at(2).at(3)),stod(configs.at(2).at(4)),stod(configs.at(2).at(5)),stod(configs.at(2).at(6)));
  }
  if(RemoveWhitespaces(configs.at(0).at(1))=="uniform"){
    vtx_gen_mode=2;
    vtx_gen.SetUniformVtx(stod(configs.at(3).at(1)),stod(configs.at(3).at(2)),stod(configs.at(3).at(3)),stod(configs.at(3).at(4)),stod(configs.at(3).at(5)),stod(configs.at(3).at(6)));
  }
  if(RemoveWhitespaces(configs.at(0).at(1))=="custom"){
    vtx_gen_mode=3;
    vtx_gen.SetCustomVtx(RemoveWhitespaces(configs.at(4).at(1)),RemoveWhitespaces(configs.at(5).at(1)),RemoveWhitespaces(configs.at(6).at(1)),RemoveWhitespaces(configs.at(7).at(1)),RemoveWhitespaces(configs.at(8).at(1)),RemoveWhitespaces(configs.at(9).at(1)));
  }
  if(RemoveWhitespaces(configs.at(10).at(1))=="constant"){
    mult_gen_mode=0;
    mult_gen.SetConstMultiplicity(stod(configs.at(11).at(1)));
  }
  if(RemoveWhitespaces(configs.at(10).at(1))=="gaussian"){
    mult_gen_mode=1;
    mult_gen.SetGausMultiplicity(stod(configs.at(12).at(1)),stod(configs.at(12).at(2)));
  }
  if(RemoveWhitespaces(configs.at(10).at(1))=="uniform"){
    mult_gen_mode=2;
    mult_gen.SetUniformMultiplicity(stod(configs.at(13).at(1)),stod(configs.at(13).at(2)));
  }
  if(RemoveWhitespaces(configs.at(10).at(1))=="custom"){
    mult_gen_mode=3;
    mult_gen.SetCustomMultiplicity(RemoveWhitespaces(configs.at(14).at(1)),RemoveWhitespaces(configs.at(15).at(1)));
  }
  if(RemoveWhitespaces(configs.at(16).at(1))=="uniform"){
    track_gen_mode=0;
    track_gen.SetUniformTrack(stod(configs.at(17).at(1)),stod(configs.at(17).at(2)));
  }
  if(RemoveWhitespaces(configs.at(16).at(1))=="custom"){
    track_gen_mode=1;
    track_gen.SetCustomTrack(RemoveWhitespaces(configs.at(18).at(1)),RemoveWhitespaces(configs.at(19).at(1)));
  }
  if(RemoveWhitespaces(configs.at(20).at(1)=="off")this->is_scattering = kFALSE;
  else is_scattering = kTRUE;

//Detector Configuration
  this->BP_radius = stod(configs.at(22).at(1));
  this->BP_thickness = stod(configs.at(23).at(1));
  this->L1_radius = stod(configs.at(24).at(1));
  this->L1_thickness = stod(configs.at(25).at(1));
  this->zmin_detector = stod(configs.at(26).at(1));
  this->zmax_detector = stod(configs.at(27).at(1));
  
//Tree Configuration
  tree->Branch("Vertex",&VTX);
  tree->Branch("Multiplicity",&multiplicity);
  tree->Branch("L1_Hits",&ptr_L1_hits);
  tree->Branch("L2_Hits",&ptr_L2_hits);
}

void NewEvent(){
  switch(vtx_gen_mode){
    case 0 : VTX = vtx_gen.GetConstVtx();
     break;
    case 1 : VTX = vtx_gen.GetGausVtx();
     break;
    case 2 : VTX = vtx_gen.GetUniformVtx();
     break;
    case 3 : VTX = vtx_gen.GetCustomVtx();
  }
  
  switch(mult_gen_mode){
    case 0 : multiplicity = mult_gen.GetConstMultiplicity();
     break;
    case 1 : multiplicity = mult_gen.GetGausMultiplicity();
     break;
    case 2 : multiplicity = mult_gen.GetUniformMultiplicity();
     break;
    case 3 : multiplicity = mult_gen.GetCustomMultiplicity();
     break;
  }
  
  switch(track_gen_mode){
    case 0 : {
      for (Int_t i=0;i<multiplicity;i++){
	ptr_tracks->AddAtAndExpand(track_gen->GetUniformTrack(),i);
      }
    }
    break;
    case 1 : {
      for (Int_t i=0;i<multiplicity;i++){
	ptr_tracks->AddAtAndExpand(track_gen->GetCustomTrack(),i);
      }
    }
    break;
  }
  
  
}

void EventGenerator::RemoveWhitespaces(string& s){
  s.erase(std::remove_if(s.begin(),s.end(),std::isspace),s.end());
}
