//: C11:UseLog2.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} UseLog1 LogFile ../TestSuite/Test
#include "UseLog1.h"
#include "LogFile.h"
using namespace std;

void g() {
  logfile() << __FILE__ << endl;
} 

int main() {
  f();
  g();
} ///:~
