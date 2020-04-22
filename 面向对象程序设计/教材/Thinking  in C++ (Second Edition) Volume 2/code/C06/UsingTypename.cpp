//: C06:UsingTypename.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Using 'typename' in the template argument list
//{L} ../TestSuite/Test

template<typename T> class X { }; 

int main() {
  X<int> x;
} ///:~
