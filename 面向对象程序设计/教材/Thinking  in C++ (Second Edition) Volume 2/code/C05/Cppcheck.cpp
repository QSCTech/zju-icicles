//: C05:Cppcheck.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Configures .h & .cpp files to conform to style
// standard. Tests existing files for conformance.
//{L} ../TestSuite/Test
#include "../require.h"
#include <fstream>
#include <strstream>
#include <string>
using namespace std;

void cppCheck(string fileName) {
  enum bufs { base, header, implement,
    Hline1, guard1, guard2, guard3,
    CPPline1, include, bufnum };
  string part[bufnum + 1];
  part[base] = fileName;
  // Find any '.' in the string:
  int loc = part[base].find('.');
  if(loc != string::npos) 
    part[base][loc] = 0; // Strip extension
  // Force to upper case:
  for(int i = 0; i < part[base].size(); i++)
    part[base][i] = toupper(part[base][i]);
  // Create file names and internal lines:
  part[header] = part[base] + ".h";
  part[implement] = part[base] + ".cpp";
  part[Hline1] = string("//") + string(": ") 
    + part[header] + " -- ";
  part[guard1] = "#ifndef " + part[base] + "_H";
  part[guard2] = "#define " + part[base] + "_H";
  part[guard3] = "#endif // " + part[base] +"_H";
  part[CPPline1] = string("//") + ": " 
    + part[implement] + " -- ";
  part[include] = "#include \"" + part[header] 
    + "\"";
  // First, try to open existing files:
  ifstream existh(part[header].c_str()),
           existcpp(part[implement].c_str());
  if(!existh) { // Doesn't exist; create it
    ofstream newheader(part[header].c_str());
    assure(newheader, part[header].c_str());
    newheader << part[Hline1] << endl
      << part[guard1] << endl
      << part[guard2] << endl << endl
      << part[guard3] << endl;
  }
  if(!existcpp) { // Create cpp file
    ofstream newcpp(part[implement].c_str());
    assure(newcpp, part[implement].c_str());
    newcpp << part[CPPline1] << endl
      << part[include] << endl;
  }
  if(existh) { // Already exists; verify it
    strstream hfile; // Write & read
    ostrstream newheader; // Write
    hfile << existh.rdbuf() << ends;
    // Check that first line conforms:
    string s;
    if(getline(hfile, s)) {
      if(s.find("//" ":") == string::npos ||
         s.find(part[header]) == string::npos)
        newheader << part[Hline1] << endl;
    }
    // Ensure guard lines are in header:
    string head = string(hfile.str());
    if(head.find(part[guard1]) == string::npos ||
      head.find(part[guard2]) == string::npos ||
      head.find(part[guard3]) == string::npos) {
       newheader << part[guard1] << endl
         << part[guard2] << endl
         << s
         << hfile.rdbuf() << endl
         << part[guard3] << endl << ends;
    } else
      newheader << s
        << hfile.rdbuf() << ends;
    // If there were changes, overwrite file:
    if(strcmp(hfile.str(),newheader.str())!=0){
      existh.close();
      ofstream newH(part[header].c_str());
      assure(newH, part[header].c_str());
      newH << "//@//" << endl // Change marker
        << newheader.rdbuf();
    }
    delete hfile.str();
    delete newheader.str();
  }
  if(existcpp) { // Already exists; verify it
    strstream cppfile;
    ostrstream newcpp;
    cppfile << existcpp.rdbuf() << ends;
    string s;
    // Check that first line conforms:
    if(getline(cppfile, s))
      if(s != "//" ":" || s != part[implement])
        newcpp << part[CPPline1] << endl;
    // Ensure header is included:
    if(string(cppfile.str()) != part[include])
      newcpp << part[include] << endl;
    // Put in the rest of the file:
    newcpp << s << endl; // First line read
    newcpp << cppfile.rdbuf() << ends;
    // If there were changes, overwrite file:
    if(string(cppfile.str()) != string(newcpp.str())){
      existcpp.close();
      ofstream newCPP(part[implement].c_str());
      assure(newCPP, part[implement].c_str());
      newCPP << "//@//" << endl // Change marker
        << newcpp.rdbuf();
    }
    delete cppfile.str();
    delete newcpp.str();
  }
}

int main(int argc, char* argv[]) {
  if(argc > 1)
    cppCheck(argv[1]);
  else
    cppCheck("cppCheckTest.h");
} ///:~
