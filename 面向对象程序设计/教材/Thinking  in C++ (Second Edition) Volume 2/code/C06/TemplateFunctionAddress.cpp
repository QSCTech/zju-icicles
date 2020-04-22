//: C06:TemplateFunctionAddress.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Taking the address of a function generated
// from a template.
//{L} ../TestSuite/Test

template <typename T> void f(T*) {}

void h(void (*pf)(int*)) {}

template <class T> 
  void g(void (*pf)(T*)) {}

int main() {
  // Full type exposition:
  h(&f<int>);
  // Type induction:
  h(&f);
  // Full type exposition:
  g<int>(&f<int>);
  // Type inductions:
  g(&f<int>);
  g<int>(&f);
} ///:~
