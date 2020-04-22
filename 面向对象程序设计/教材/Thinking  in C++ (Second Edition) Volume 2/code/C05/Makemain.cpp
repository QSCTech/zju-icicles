//: C05:Makemain.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Create a shell main() file
//{L} ../TestSuite/Test
#include "../require.h"
#include <fstream>
#include <strstream>
#include <cstring>
#include <cctype>
using namespace std;

void makeMain(char* fileName) {
  ofstream mainfile(fileName);
  assure(mainfile, fileName);
  istrstream name(fileName);
  ostrstream CAPname;
  char c;
  while(name.get(c))
    CAPname << char(toupper(c));
  CAPname << ends;
  mainfile << "//" << ": " << CAPname.rdbuf()
    << " -- " << endl
    << "#include <iostream>" << endl
    << endl
    << "main() {" << endl << endl
    << "}" << endl;
}

int main(int argc, char* argv[]) {
  if(argc > 1)
    makeMain(argv[1]);
  else
    makeMain("mainTest.cpp");
} ///:~
