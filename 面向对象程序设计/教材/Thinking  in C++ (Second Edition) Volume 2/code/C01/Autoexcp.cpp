//: C01:Autoexcp.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// No matching conversions
//{L} ../TestSuite/Test
#include <iostream>
using namespace std;

class Except1 {};
class Except2 {
public:
  Except2(Except1&) {}
};

void f() { throw Except1(); }

int main() {
  try { f();
  } catch (Except2) {
    cout << "inside catch(Except2)" << endl;
  } catch (Except1) {
    cout << "inside catch(Except1)" << endl;
  }
} ///:~
