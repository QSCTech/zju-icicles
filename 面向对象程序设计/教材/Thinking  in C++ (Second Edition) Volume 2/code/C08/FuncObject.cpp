//: C08:FuncObject.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Simple function objects
//{L} ../TestSuite/Test
#include <iostream>
using namespace std;

template<class UnaryFunc, class T>
void callFunc(T& x, UnaryFunc f) {
  f(x);
}

void g(int& x) {
  x = 47;
}

struct UFunc {
  void operator()(int& x) {
    x = 48;
  }
};

int main() {
  int y = 0;
  callFunc(y, g);
  cout << y << endl;
  y = 0;
  callFunc(y, UFunc());
  cout << y << endl;
} ///:~
