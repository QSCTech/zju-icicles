//: C11:TrashProtoInit.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Performs initialization of all the prototypes.
// Create a different version of this file to
// make different kinds of Trash.
#include "Trash.h"
#include "Aluminum.h"
#include "Paper.h"
#include "Glass.h"
#include "Cardboard.h"

// Allocate the static member object:
std::vector<Trash*> Trash::prototypes;

class TrashProtoInit {
  Aluminum a;
  Paper p;
  Glass g;
  Cardboard c;
  TrashProtoInit() {
    Trash::prototypes.push_back(&a);
    Trash::prototypes.push_back(&p);
    Trash::prototypes.push_back(&g);
    Trash::prototypes.push_back(&c);
  }
  static TrashProtoInit singleton;
};

TrashProtoInit 
  TrashProtoInit::singleton; ///:~
