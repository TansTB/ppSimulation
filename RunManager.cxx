#include<iostream>
#include<fstream>
#include<vector>
#include<string>
// #include"EventGenerator.h"
#include"MyParser.h"
int main(){
  vector<vector<string> > v;
  ifstream config("Config.txt");
  ColonParser(config,v);
//test
//   for (vector<string> i : v){
//     for(string j : i){
//       std::cout << j <<" ";
//       
//     }
//     std::cout<<std::endl;
//   }
  return 0;
}