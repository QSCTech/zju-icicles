//: C11:Recycle4.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} TrashProtoInit ../TestSuite/Test
//{L} fillBin Trash TrashStat
// Adding TrashBins and TrashSorters
#include "Trash.h"
#include "Aluminum.h"
#include "Paper.h"
#include "Glass.h"
#include "Cardboard.h"
#include "fillBin.h"
#include "sumValue.h"
#include "../purge.h"
#include <fstream>
#include <vector>
using namespace std;
ofstream out("Recycle4.out");

class TBin : public vector<Trash*> {
public:
  virtual bool grab(Trash*) = 0;
};

template<class TrashType>
class TrashBin : public TBin {
public:
  bool grab(Trash* t) {
    TrashType* tp = dynamic_cast<TrashType*>(t);
    if(!tp) return false; // Not grabbed
    push_back(tp);
    return true; // Object grabbed
  }
};

class TrashSorter : public vector<TBin*> {
public:
  bool sort(Trash* t) {
    for(iterator it = begin(); it != end(); it++)
      if((*it)->grab(t))
        return true;
    return false;
  }
  void sortBin(vector<Trash*>& bin) {
    vector<Trash*>::iterator it;
    for(it = bin.begin(); it != bin.end(); it++)
      if(!sort(*it))
        cerr << "bin not found" << endl;
  }
  ~TrashSorter() { purge(*this); }
};

int main() {
  vector<Trash*> bin;
  // Fill up the Trash bin:
  fillBin("Trash.dat", bin);
  TrashSorter tbins;
  tbins.push_back(new TrashBin<Aluminum>);
  tbins.push_back(new TrashBin<Paper>);
  tbins.push_back(new TrashBin<Glass>);
  tbins.push_back(new TrashBin<Cardboard>);
  tbins.sortBin(bin);
  for(TrashSorter::iterator it = tbins.begin(); 
    it != tbins.end(); it++)
    sumValue(**it);
  sumValue(bin);
  purge(bin);
} ///:~
