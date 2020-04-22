//: C04:SiteMapConvert.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using strings to create a custom conversion
// program that generates HTML output
#include "../require.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Item {
  string id, url;
  int depth;
  string removeBar(string s) {
    if(s[0] == '|')
      return s.substr(1);
    else return s;
  }
public:
  Item(string in, int& index) : depth(0) {
    while(in[index] == '#' && index < in.size()){
      depth++;
      index++;
    }
    // 0 means no '#' marks were found:
    if(depth == 0) depth = 1;
    while(in[index] != '%' && index < in.size())
      id += in[index++];
    id = removeBar(id);
    index++; // Move past '%'
    while(in[index] != '*' && index < in.size())
      url += in[index++];
    url = removeBar(url);
    index++; // To move past '*'
  }
  string identifier() { return id; }
  string path() { return url; }
  int level() { return depth; }
};

int main(int argc, char* argv[]) {
  requireArgs(argc, 1,
    "usage: SiteMapConvert inputfilename");
  ifstream in(argv[1]);
  assure(in, argv[1]);
  ofstream out("plainmap.html");
  string line;
  while(getline(in, line)) {
    if(line.find("<param name=\"source_file\"")
       != string::npos) {
      // Extract data from start of sequence
      // until the terminating quote mark:
      line = line.substr(line.find("value=\"") 
             + string("value=\"").size());
      line = line.substr(0, 
               line.find_last_of("\""));
      int index = 0;
      while(index < line.size()) {
        Item item(line, index);
        string startLevel, endLevel;
        if(item.level() == 1) {
          startLevel = "<h1>";
          endLevel = "</h1>";
        } else
          for(int i = 0; i < item.level(); i++)
            for(int j = 0; j < 5; j++)
              out << "&nbsp;";
        string htmlLine = "<a href=\""
          + item.path() + "\">"
          + item.identifier() + "</a><br>";
        out << startLevel << htmlLine 
            << endLevel << endl;
      }
      break; // Out of while loop
    }
  }
} ///:~
