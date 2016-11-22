#include "EventGenerator"

EventGenerator::EventGenerator(vector<strings> configs,TTree *tree){
  //Generator Configuration
  this->tree = tree;
  if(configs.at(0)=="constant")vtx_gen_mode=0;
  if(configs.at(0)=="gaussian")vtx_gen_mode=1;
  if(configs.at(0)=="uniform")vtx_gen_mode=2;
  if(configs.at(0)=="custom")vtx_gen_mode=3;
  if(configs.at(8)=="constant")mult_gen_mode=0;
  if(configs.at(8)=="gaussian")mult_gen_mode=1;
  if(configs.at(8)=="uniform")mult_gen_mode=2;
  if(configs.at(8)=="custom")mult_gen_mode=3;
  if(configs.at(14)=="uniform")track_gen_mode=0;
  if(configs.at(14)=="custom")track_gen_mode=0;
}

void EventGenerator::RemoveWhitespaces(string& s){
  s.erase(std::remove_if(s.begin(),s.end(),std::isspace),s.end());
}
