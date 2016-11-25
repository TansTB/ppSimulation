#include "EventGenerator"

using namespace std;
using namespace TMath;

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
  this->BP_X0 = stod(configs.at(24).at(1));
  this->BP_Z = stod(configs.at(25).at(1));
  this->L1_radius = stod(configs.at(26).at(1));
  this->L1_thickness = stod(configs.at(27).at(1));
  this->L1_X0 = stod(configs.at(28).at(1));
  this->L1_Z = stod(configs.at(29).at(1));
  this->zmin_detector = stod(configs.at(30).at(1));
  this->zmax_detector = stod(configs.at(31).at(1));
  this->p = stod(configs.at(32).at(1));
  this->BP_theta0 = Sqrt((2.*BP_thickness)/BP_X0)*13.6*BP_Z*(1+0.038*Log(BP_thickness/BP_X0))/p;
  this->L1_theta0 = Sqrt((2.*L1_thickness)/L1_X0)*13.6*L1_Z*(1+0.038*Log(L1_thickness/L1_X0))/p;
  
//Tree Configuration
  tree->Branch("Vertex",&VTX);
  tree->Branch("Multiplicity",&multiplicity);
  tree->Branch("L1_Hits",&ptr_L1_hits);
  tree->Branch("L2_Hits",&ptr_L2_hits);
}

EventGenerator::~EventGenerator(){
  delete ptr_tracks;
  delete ptr_BP_hits;
  delete ptr_L1_hits;
  delete ptr_L2_hits;
}

void NewEvent(){
  //Generate Vertex
  switch(vtx_gen_mode){
    case 0 : VTX = vtx_gen.GetConstVtx();
     break;
    case 1 : VTX = vtx_gen.GetGausVtx();
     break;
    case 2 : VTX = vtx_gen.GetUniformVtx();
     break;
    case 3 : VTX = vtx_gen.GetCustomVtx();
  }
  //Generate Multiplicity
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
  //Generate Tracks
  switch(track_gen_mode){
    case 0 : {
      for (Int_t i=0;i<multiplicity;i++){
	new(tracks[i]) Track(*(track_gen->GetUniformTrack()));
      }
    }
    break;
    case 1 : {
      for (Int_t i=0;i<multiplicity;i++){
	new(tracks[i]) Track(*(track_gen->GetCustomTrack()));
      }
    }
    break;
  } 
  //Calculating Hits
  for (Int_t label=0;label<multiplicity;label++){
    Hit* intersection;
    Int_t c1=0,c2=0,c3=0;
    if(Intersection(VTX,tracks.At(label),BP_radius,intersection)){
      intersection->SetLabel(label);
      new(BP_hits[c1]) Hit(*intersection);
      if(is_scattering)tracks.At(label) = MultipleScattering(tracks.At(label),BP_theta0);
      if(Intersection(BP_hits.At(c1),1,tracks.At(label),L1_radius,intersection)){
	new(L1_hits[c2]) Hit(*intersection);
	if(is_scattering)tracks.At(label) = MultipleScattering(tracks.At(label),L1_theta0);
	if(Intersection(L1_Hits.At(c2),2,tracks.At(label),L2_radius,intersection){
	  new(L2_hits[c2]) Hit(*intersection);
	  c3++;
	}
	c2++;
      }
      c1++;
    }
  }
  tree->Fill();
  ptr_BP_hits->Clear();
  ptr_L1_hits->Clear();
  ptr_L2_hits->Clear();
}

Bool_t EventGenerator::Intersection(Point* vertex,Track* track,Double_t radius,Hit* intersection){
  Double_t t,delta,x,y,z;
  delta = Power((vertex->GetX())*Sin(track->GetTheta())*Cos(track->GetPhi())+(vertex->GetY())*Sin(track->GetTheta())*Sin(track->GetPhi()),2)-(Power(Sin(track->GetTheta())*Cos(track->GetPhi()),2)+Power(Sin(track->GetTheta())*Sin(track->GetPhi()),2))*(Power(vertex->GetX(),2)+Power(vertex->GetY(),2)-Power(radius,2));
  t = (-((vertex->GetX())*Sin(track->GetTheta())*Cos(track->GetPhi())+(vertex->GetY())*Sin(track->GetTheta())*Sin(track->GetPhi()))+Sqrt(delta))/(Power(Sin(track->GetTheta())*Cos(track->GetPhi()),2)+Power(Sin(track->GetTheta())*Sin(track->GetPhi()),2));
  x = (vertex->GetX())+t*Sin(track->GetTheta())*Cos(track->GetPhi());
  y = (vertex->GetY())+t*Sin(track->GetTheta())*Sin(track->GetPhi());
  z = (vertex->GetZ())+t*Cos(track->GetTheta());
  intersection->SetPhi(Atan(y/x));
  intersection->SetZ(z);
  if((zmin_detector<z)&&(z<zmax_detector))return kTRUE;
  else return kFALSE;
}

Bool_t EventGenerator::Intersection(Hit* layer_hit,Int_t layer_hit_number,Track* track,Double_t radius,Hit* intersection){
  Double_t vertex_radius = (layer_hit_number==0) ? BP_radius : L1_radius;
  Point vtx = Point(vertex_radius*(Cos(layer_hit->GetPhi())),vertex_radius*(Sin(layer_hit->GetPhi())),(layer_hit->GetZ()));
  Point* vertex = &vtx;
  return Intersection(vertex,track,radius,intersection);
}

Track* EventGenerator::MultipleScattering(Track* track,Double_t theta0rms){
  track->Rotate(gRandom->Gaus(0,theta0rms),Uniform(0,2*Pi()));
}

string EventGenerator::RemoveWhitespaces(string& s){
  s.erase(std::remove_if(s.begin(),s.end(),[](char c){return std::isspace(static_cast<unsigned char>(c));}),s.end());
  return s;
}
