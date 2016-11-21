//CSVParser.h
//****************************************************
//This lib contains the method used to parse multiple 
//lines files and transfer all the lines in a vector 
//of strings
//****************************************************

#ifndef MYPARSER_H
#define MYPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void LineParser(ifstream&, vector<string>&);//Function to turn a multiple lines file into a vector of strings 
void CSVParser(ifstream& file_to_parse, vector<vector<string> >&);//Function to turn a vector of lines coming from a .csv in a vector
								  //of vectors containing the fields. spreadsheet should be empty
#endif
