//: C11:Trash.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#include "Trash.h"
using namespace std;

Trash* Trash::factory(const Info& info) {
  vector<Trash*>::iterator it;
  for(it = prototypes.begin();
    it != prototypes.end(); it++) {
    // Somehow determine the new type
    // to create, and clone one:
    if (info.id() == (*it)->id())
      return (*it)->clone(info);
  }
  cerr << "Prototype not found for "
    << info << endl;
  // "Default" to first one in the vector:
  return (*prototypes.begin())->clone(info);
} ///:~
