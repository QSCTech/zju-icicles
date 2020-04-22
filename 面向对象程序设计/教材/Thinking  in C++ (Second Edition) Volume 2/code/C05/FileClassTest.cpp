//: C05:FileClassTest.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} FileClass ../TestSuite/Test
//{-msc}
// Testing class File
#include "FileClass.h"
using namespace std;

int main() {
  // Opens and tests:
  FileClass f("FileClassTest.cpp"); 
  const int bsize = 100;
  char buf[bsize];
  while(fgets(buf, bsize, f.fp()))
    puts(buf);
} // File automatically closed by destructor
///:~
