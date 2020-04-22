//: C11:DoubleDispatch.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} DDTrashProtoInit ../TestSuite/Test
//{L} fillBin Trash TrashStat
//{-msc}
// Using multiple dispatching to handle more than
// one unknown type during a member function call
#include "TypedBin.h"
#include "fillBin.h"
#include "sumValue.h"
#include "../purge.h"
#include <iostream>
#include <fstream>
using namespace std;
ofstream out("DoubleDispatch.out");

class TrashBinSet : public vector<TypedBin*> {
public:
  TrashBinSet() {
    push_back(new BinOf<DD<Aluminum> >);
    push_back(new BinOf<DD<Paper> >);
    push_back(new BinOf<DD<Glass> >);
    push_back(new BinOf<DD<Cardboard> >);
  };
  void sortIntoBins(vector<Trash*>& bin) {
    vector<Trash*>::iterator it;
    for(it = bin.begin(); it != bin.end(); it++)
      // Perform the double dispatch:
      if(!(*it)->addToBin(*this))
        cerr << "Couldn't add " << *it << endl;
  }
  ~TrashBinSet() { purge(*this); }
};

int main() {
  vector<Trash*> bin;
  TrashBinSet bins;
  // fillBin() still works, without changes, but
  // different objects are cloned:
  fillBin("Trash.dat", bin);
  // Sort from the master bin into the
  // individually-typed bins:
  bins.sortIntoBins(bin);
  TrashBinSet::iterator it;
  for(it = bins.begin(); it != bins.end(); it++)
    sumValue(**it);
  // ... and for the master bin
  sumValue(bin);
  purge(bin);
} ///:~
