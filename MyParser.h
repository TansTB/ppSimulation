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
#include <algorithm>
#include <stdlib.h>

using namespace std;

void LineParser(ifstream& file_to_parse, vector<string>& lines);//Function to turn a multiple lines file into a vector of strings 
void CSVParser(ifstream& file_to_parse, vector<vector<string> >& spreadsheet);//Function to turn a .csv file in a vector
								  //of vectors containing the fields. spreadsheet should be empty
void ColonParser(ifstream& file_to_parse, vector<vector<string> >& spreadsheet);//Function to turn a colon separated .txt file in a vector
								  //of vectors containing the fields. spreadsheet should be empty
string RemoveWhitespaces(string& s); //Function to remove whitespaces from a string
#endif
