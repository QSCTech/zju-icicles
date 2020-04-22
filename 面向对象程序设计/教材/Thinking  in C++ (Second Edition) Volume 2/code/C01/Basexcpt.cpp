//: C01:Basexcpt.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Exception hierarchies
//{L} ../TestSuite/Test
#include <iostream>
using namespace std;

class X {
public:
  class Trouble {};
  class Small : public Trouble {};
  class Big : public Trouble {};
  void f() { throw Big(); }
};

int main() {
  X x;
  try {
    x.f();
  } catch(X::Trouble) {
    cout << "caught Trouble" << endl;
  // Hidden by previous handler:
  } catch(X::Small) {
    cout << "caught Small Trouble" << endl;
  } catch(X::Big) {
    cout << "caught Big Trouble" << endl;
  }
} ///:~
