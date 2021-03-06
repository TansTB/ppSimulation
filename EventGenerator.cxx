#include "EventGenerator.h"

using namespace std;
using namespace TMath;

EventGenerator::EventGenerator(vector<vector<string> > configs,TTree *tree){
//Generator Configuration
this->tree = tree;
cout<<"Configuring the generator..."<<endl;
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
    vtx_gen.SetCustomVtx(RemoveWhitespaces(configs.at(4).at(1)).c_str(),RemoveWhitespaces(configs.at(5).at(1)).c_str(),RemoveWhitespaces(configs.at(6).at(1)).c_str(),RemoveWhitespaces(configs.at(7).at(1)).c_str(),RemoveWhitespaces(configs.at(8).at(1)).c_str(),RemoveWhitespaces(configs.at(9).at(1)).c_str());
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
    mult_gen.SetCustomMultiplicity(RemoveWhitespaces(configs.at(14).at(1)).c_str(),RemoveWhitespaces(configs.at(15).at(1)).c_str());
}
if(RemoveWhitespaces(configs.at(16).at(1))=="uniform"){
    track_gen_mode=0;
    track_gen.SetUniformTrack(stod(configs.at(17).at(1)),stod(configs.at(17).at(2)));
}
if(RemoveWhitespaces(configs.at(16).at(1))=="custom"){
    track_gen_mode=1;
    track_gen.SetCustomTrack(RemoveWhitespaces(configs.at(18).at(1)).c_str(),RemoveWhitespaces(configs.at(19).at(1)).c_str());
}
if(RemoveWhitespaces(configs.at(20).at(1))=="off"){this->is_scattering = kFALSE;}
else{is_scattering = kTRUE;}

//Detector Configuration
this->BP_radius = stod(configs.at(24).at(1));
this->BP_thickness = stod(configs.at(25).at(1));
this->BP_X0 = stod(configs.at(26).at(1));
this->BP_Z = stod(configs.at(27).at(1));
this->L1_radius = stod(configs.at(28).at(1));
this->L1_thickness = stod(configs.at(29).at(1));
this->L1_X0 = stod(configs.at(30).at(1));
this->L1_Z = stod(configs.at(31).at(1));
this->L2_radius = stod(configs.at(32).at(1));
this->zmin_detector = stod(configs.at(33).at(1));
this->zmax_detector = stod(configs.at(34).at(1));
this->zres_detector = stod(configs.at(35).at(1));
this->rphires_detector = stod(configs.at(36).at(1));
this->p = stod(configs.at(37).at(1));
this->BP_theta0 = Sqrt((BP_thickness)/BP_X0)*13.6*BP_Z*(1+0.038*Log(BP_thickness/BP_X0))/p;
this->L1_theta0 = Sqrt((L1_thickness)/L1_X0)*13.6*L1_Z*(1+0.038*Log(L1_thickness/L1_X0))/p;
//   cout << L1_theta0 <<endl;


//Tree Configuration
tree->Branch("Vertex",&VTX);
cout<<"Creating Tree Branches..."<<endl;
tree->Branch("Multiplicity",&multiplicity);
tree->Branch("L1_Hits","TClonesArray",&ptr_L1_hits_recorded);
tree->Branch("L2_Hits","TClonesArray",&ptr_L2_hits_recorded);

//Noise Configuration
if(RemoveWhitespaces(configs.at(42).at(1))=="false") is_noise=kFALSE;     //noise off

if(RemoveWhitespaces(configs.at(42).at(1))=="true"){ 
    is_noise=kTRUE;                                                        //noise on           
}
if(RemoveWhitespaces(configs.at(38).at(1))=="constant"){
    noise_mode=0;
    n.SetConstantEntriesNumber(stod(configs.at(39).at(1)));       
}
if(RemoveWhitespaces(configs.at(38).at(1))=="custom"){
    noise_mode=1;
    n.SetCustomEntriesNumber(RemoveWhitespaces(configs.at(40).at(1)).c_str(),RemoveWhitespaces(configs.at(41).at(1)).c_str());
}
}

EventGenerator::~EventGenerator(){
delete ptr_tracks;
delete ptr_BP_hits;
delete ptr_L1_hits;
delete ptr_L2_hits;
delete ptr_L1_hits_recorded;
delete ptr_L2_hits_recorded;
delete def_vtx;
delete intersection;
delete intersection_recorded;
}

void EventGenerator::NewEvent(){
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
//   cout << "VTX: "<<VTX->GetX()<< " "<<VTX->GetY() << " "<<VTX->GetZ() << endl;
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
//   cout<<"Multiplicity: "<<multiplicity<<endl;
//Generate Tracks
switch(track_gen_mode){
    case 0 : {
    for (Int_t i=0;i<multiplicity;i++){
    new(tracks[i]) Track(*(track_gen.GetUniformTrack()));
    }
    }
    break;
    case 1 : {
    for (Int_t i=0;i<multiplicity;i++){
    new(tracks[i]) Track(*(track_gen.GetCustomTrack()));
    }
    }
    break;
} 

//Calculating Hits
    Int_t c1=0,c2=0,c3=0,aux=0;
for (Int_t label=0;label<multiplicity;label++){
    aux = Intersection(VTX,(Track*)tracks.At(label),BP_radius,intersection);
//       cout << "Track: " <<((Track*)tracks.At(label))->GetPhi();
    intersection->SetLabel(label);
    intersection_recorded->SetLabel(label);
    new(BP_hits[c1]) Hit(*intersection);
    if(is_scattering) MultipleScattering((Track*)tracks.At(label),BP_theta0);
    if(Intersection((Hit*)BP_hits.At(c1),0,(Track*)tracks.At(label),L1_radius,intersection)){
        intersection_recorded->SetZ(gRandom->Gaus(intersection->GetZ(),zres_detector));
        intersection_recorded->SetPhi(gRandom->Gaus(intersection->GetPhi(),rphires_detector/L1_radius));
//         cout << "\tL1 " << intersection->GetPhi();
        new(L1_hits[c2]) Hit(*intersection);
        new(L1_hits_recorded[c2]) Hit(*intersection_recorded);
        if(is_scattering) MultipleScattering((Track*)tracks.At(label),L1_theta0);
        if(Intersection((Hit*)L1_hits.At(c2),1,(Track*)tracks.At(label),L2_radius,intersection)){
//             cout << "\tL2 " << intersection->GetPhi();
            intersection_recorded->SetZ(gRandom->Gaus(intersection->GetZ(),zres_detector));
            intersection_recorded->SetPhi(gRandom->Gaus(intersection->GetPhi(),rphires_detector/L2_radius));
            new(L2_hits[c3]) Hit(*intersection);
            new(L2_hits_recorded[c3]) Hit(*intersection_recorded);
            c3++;
//             cout << "gotcha"<<endl;
        }
//         else cout << "missed2L" <<endl;
        c2++;
    }
//       else cout <<"missed1L"<<endl;
    c1++;
//       cout<<endl;
}

//Add noise
if (is_noise){
    this->n.VariableEntries(noise_mode);
    this->n.SetParameters(zmin_detector,zmax_detector);
    this->n.NewNoise(ptr_L1_hits_recorded);
    this->n.NewNoise(ptr_L2_hits_recorded);
}

tree->Fill();
ptr_BP_hits->Clear();
ptr_L1_hits->Clear();
ptr_L2_hits->Clear();
ptr_L1_hits_recorded->Clear();
ptr_L2_hits_recorded->Clear();    
}


Bool_t EventGenerator::Intersection(Point* vertex,Track* track,Double_t radius,Hit* intersection){
    Double_t t,delta,x,y,z;
    delta = Power((vertex->GetX())*Sin(track->GetTheta())*Cos(track->GetPhi())+(vertex->GetY())*Sin(track->GetTheta())*Sin(track->GetPhi()),2)-(Power(Sin(track->GetTheta())*Cos(track->GetPhi()),2)+Power(Sin(track->GetTheta())*Sin(track->GetPhi()),2))*(Power(vertex->GetX(),2)+Power(vertex->GetY(),2)-Power(radius,2));
    t = (-((vertex->GetX())*Sin(track->GetTheta())*Cos(track->GetPhi())+(vertex->GetY())*Sin(track->GetTheta())*Sin(track->GetPhi()))+Sqrt(delta))/(Power(Sin(track->GetTheta())*Cos(track->GetPhi()),2)+Power(Sin(track->GetTheta())*Sin(track->GetPhi()),2));
    x = (vertex->GetX())+t*Sin(track->GetTheta())*Cos(track->GetPhi());
    y = (vertex->GetY())+t*Sin(track->GetTheta())*Sin(track->GetPhi());
    z = (vertex->GetZ())+t*Cos(track->GetTheta());
    if(x>0)intersection->SetPhi(ATan(y/x));
    else{
        if(y>0)intersection->SetPhi(Pi()+ATan(y/x));
        else intersection->SetPhi(-Pi()+ATan(y/x));
    }
    if (x==0){if(y>0)intersection->SetPhi(Pi()/2);
        else intersection->SetPhi(-Pi()/2);
    }
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

void EventGenerator::MultipleScattering(Track* track,Double_t theta0rms){
    track->Rotate(gRandom->Gaus(0,theta0rms),gRandom->Uniform(-Pi(),Pi()));
}
