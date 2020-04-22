//: C11:VisitorTrashPInit.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#include "Visitor.h"

std::vector<Trash*> Trash::prototypes;

class TrashProtoInit {
  Visitable<Aluminum> a;
  Visitable<Paper> p;
  Visitable<Glass> g;
  Visitable<Cardboard> c;
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
