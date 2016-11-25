#include "MyParser.h"

using namespace std;

void LineParser(ifstream& file_to_parse, vector<string>& lines){
  if (!file_to_parse)
  {
    printf("ERROR in LineParser > file not found.\n");
    exit(1);
    
  }
  while (true){      
    if (file_to_parse.eof()){break;}  
    string line;
    getline(file_to_parse,line);
    if (line[0] != '#' && line.size() > 0){
      lines.push_back(line);
    }
  }  
}

void CSVParser(ifstream& file_to_parse,vector<vector<string> >& spreadsheet){
  vector<string> lines;
  LineParser(file_to_parse,lines);
  for (vector<string>::iterator line=lines.begin();line!=lines.end();++line){
    string field_content;
    istringstream linestream(*line);
    if (!linestream.eof()){
      spreadsheet.push_back(vector<string>());
      while(1){
	getline(linestream,field_content,',');
	spreadsheet.back().push_back(field_content);
	if (linestream.eof())break;
      }
    }
  }
}

void ColonParser(ifstream& file_to_parse,vector<vector<string> >& spreadsheet){
  vector<string> lines;
  LineParser(file_to_parse,lines);
  for (vector<string>::iterator line=lines.begin();line!=lines.end();++line){
    string field_content;
    istringstream linestream(*line);
    if (!linestream.eof()){
      spreadsheet.push_back(vector<string>());
      getline(linestream,field_content,':');
      if (field_content=="//"){
	spreadsheet.pop_back();
	continue;
      }
      while(1){
	spreadsheet.back().push_back(field_content);
	if (linestream.eof())break;
	getline(linestream,field_content,':');
	if (field_content=="//")break;
      }
    }
  }
}