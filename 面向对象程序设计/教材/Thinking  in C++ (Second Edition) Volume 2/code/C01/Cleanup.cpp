//: C01:Cleanup.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Exceptions clean up objects
//{L} ../TestSuite/Test
#include <fstream>
#include <exception>
#include <cstring>
using namespace std;
ofstream out("cleanup.out");

class Noisy {
  static int i;
  int objnum;
  enum {sz = 40};
  char name[sz];
public:
  Noisy(const char* nm="array elem") throw(int){
    objnum = i++;
    memset(name, 0, sz);
    strncpy(name, nm, sz - 1);
    out << "constructing Noisy " << objnum
      << " name [" << name << "]" << endl;
    if(objnum == 5) throw int(5);
    // Not in exception specification:
    if(*nm == 'z') throw char('z');
  }
  ~Noisy() {
    out << "destructing Noisy " << objnum
      << " name [" << name << "]" << endl;
  }
  void* operator new[](size_t sz) {
    out << "Noisy::new[]" << endl;
    return ::new char[sz];
  }
  void operator delete[](void* p) {
    out << "Noisy::delete[]" << endl;
    ::delete []p;
  }
};

int Noisy::i = 0;

void unexpected_rethrow() {
  out << "inside unexpected_rethrow()" << endl;
  exit(0); // Rethrow same exception
}

int main() {
  set_unexpected(unexpected_rethrow);
  try {
    Noisy n1("before array");
    // Throws exception:
    Noisy* array = new Noisy[7];
    Noisy n2("after array");
  } catch(int i) {
    out << "caught " << i << endl;
  }
  out << "testing unexpected:" << endl;
  try {
    Noisy n3("before unexpected");
    Noisy n4("z");
    Noisy n5("after unexpected");
  } catch(char c) {
    out << "caught " << c << endl;
  }
} ///:~
