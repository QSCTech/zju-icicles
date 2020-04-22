//: C11:DDTrashProtoInit.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#include "TypedBin.h"
#include "Aluminum.h"
#include "Paper.h"
#include "Glass.h"
#include "Cardboard.h"

std::vector<Trash*> Trash::prototypes;

class TrashProtoInit {
  DD<Aluminum> a;
  DD<Paper> p;
  DD<Glass> g;
  DD<Cardboard> c;
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
