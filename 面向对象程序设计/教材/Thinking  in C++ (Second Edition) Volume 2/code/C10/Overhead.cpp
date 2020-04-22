//: C10:Overhead.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Virtual base class overhead
//{L} ../TestSuite/Test
#include <fstream>
using namespace std;
ofstream out("overhead.out");

class MBase {
public:
  virtual void f() const {};
  virtual ~MBase() {}
};

class NonVirtualInheritance
  : public MBase {};

class VirtualInheritance
  : virtual public MBase {};

class VirtualInheritance2
  : virtual public MBase {};

class MI
  : public VirtualInheritance,
    public VirtualInheritance2 {};

#define WRITE(ARG) \
out << #ARG << " = " << ARG << endl;

int main() {
  MBase b;
  WRITE(sizeof(b));
  NonVirtualInheritance nonv_inheritance;
  WRITE(sizeof(nonv_inheritance));
  VirtualInheritance v_inheritance;
  WRITE(sizeof(v_inheritance));
  MI mi;
  WRITE(sizeof(mi));
} ///:~
