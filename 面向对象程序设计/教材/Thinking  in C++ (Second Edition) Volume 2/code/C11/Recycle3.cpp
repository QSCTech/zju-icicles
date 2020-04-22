//: C11:Recycle3.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} TrashProtoInit ../TestSuite/Test
//{L} fillBin Trash TrashStat
// Recycling with RTTI and Prototypes
#include "Trash.h"
#include "Aluminum.h"
#include "Paper.h"
#include "Glass.h"
#include "fillBin.h"
#include "sumValue.h"
#include "../purge.h"
#include <fstream>
#include <vector>
using namespace std;
ofstream out("Recycle3.out");

int main() {
  vector<Trash*> bin;
  // Fill up the Trash bin:
  fillBin("Trash.dat", bin);
  vector<Aluminum*> alBin;
  vector<Paper*> paperBin;
  vector<Glass*> glassBin;
  vector<Trash*>::iterator it = bin.begin();
  while(it != bin.end()) {
    // Sort the Trash:
    Aluminum* ap = 
      dynamic_cast<Aluminum*>(*it);
    Paper* pp = dynamic_cast<Paper*>(*it);
    Glass* gp = dynamic_cast<Glass*>(*it);
    if(ap) alBin.push_back(ap);
    if(pp) paperBin.push_back(pp);
    if(gp) glassBin.push_back(gp);
    it++;
  }
  sumValue(alBin);
  sumValue(paperBin);
  sumValue(glassBin);
  sumValue(bin);
  purge(bin);
} ///:~
