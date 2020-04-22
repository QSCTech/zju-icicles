//: C11:DynaTrash.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
//{L} TrashProtoInit ../TestSuite/Test
//{L} fillBin Trash TrashStat
// Using a map of vectors and RTTI
// to automatically sort Trash into
// vectors. This solution, despite the
// use of RTTI, is extensible.
#include "Trash.h"
#include "fillBin.h"
#include "sumValue.h"
#include "../purge.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <typeinfo>
using namespace std;
ofstream out("DynaTrash.out");

// Must adapt from type_info in Standard C++,
// since type_info is too restrictive:
template<class T> // T should be a base class
class TypeInfo {
  string id;
public:
  TypeInfo(T* t) : id(typeid(*t).name()) {}
  const string& name() { return id; }
  friend bool operator<(const TypeInfo& lv,
    const TypeInfo& rv){
    return lv.id < rv.id;
  }
};

class TypeMap : 
  public map<TypeInfo<Trash>, vector<Trash*> >,
  public Fillable {
public:
  // Satisfies the Fillable interface:
  void addTrash(Trash* t) {
    (*this)[TypeInfo<Trash>(t)].push_back(t);
  }
  ~TypeMap() {
    for(iterator it = begin(); it != end(); it++)
      purge((*it).second);
  }
};

int main() {
  TypeMap bin;
  fillBin("Trash.dat", bin); // Sorting happens
  TypeMap::iterator it;
  for(it = bin.begin(); it != bin.end(); it++)
    sumValue((*it).second);
} ///:~
