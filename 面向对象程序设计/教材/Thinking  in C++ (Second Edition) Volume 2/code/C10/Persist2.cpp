//: C10:Persist2.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Improved MI persistence
//{L} ../TestSuite/Test
#include "../require.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Persistent {
public:
  virtual void write(ostream& out) const = 0;
  virtual void read(istream& in) = 0;
  virtual ~Persistent() {}
};

class Data {
protected:
  float f[3];
public:
  Data(float f0 = 0.0, float f1 = 0.0,
    float f2 = 0.0) {
    f[0] = f0;
    f[1] = f1;
    f[2] = f2;
  }
  void print(const char* msg = "") const {
    if(*msg) cout << msg << endl;
    for(int i = 0; i < 3; i++)
      cout << "f[" << i << "] = "
           << f[i] << endl;
  }
};

class WData1 : public Persistent, public Data {
public:
  WData1(float f0 = 0.0, float f1 = 0.0,
    float f2 = 0.0) : Data(f0, f1, f2) {}
  void write(ostream& out) const {
    out << f[0] << " " 
      << f[1] << " " << f[2] << " ";
  }
  void read(istream& in) {
    in >> f[0] >> f[1] >> f[2];
  }
};

class WData2 : public Data, public Persistent {
public:
  WData2(float f0 = 0.0, float f1 = 0.0,
    float f2 = 0.0) : Data(f0, f1, f2) {}
  void write(ostream& out) const {
    out << f[0] << " " 
      << f[1] << " " << f[2] << " ";
  }
  void read(istream& in) {
    in >> f[0] >> f[1] >> f[2];
  }
};

class Conglomerate : public Data,
public Persistent {
  char* name; // Contains a pointer
  WData1 d1;
  WData2 d2;
public:
  Conglomerate(const char* nm = "",
    float f0 = 0.0, float f1 = 0.0,
    float f2 = 0.0, float f3 = 0.0,
    float f4 = 0.0, float f5 = 0.0,
    float f6 = 0.0, float f7 = 0.0,
    float f8= 0.0) : Data(f0, f1, f2),
    d1(f3, f4, f5), d2(f6, f7, f8) {
    name = new char[strlen(nm) + 1];
    strcpy(name, nm);
  }
  void write(ostream& out) const {
    int i = strlen(name) + 1;
    out << i << " "; // Store size of string
    out << name << endl;
    d1.write(out);
    d2.write(out);
    out << f[0] << " " << f[1] << " " << f[2];
  }
  // Must read in same order as write:
  void read(istream& in) {
    delete []name; // Remove old storage
    int i;
    in >> i >> ws; // Get int, strip whitespace
    name = new char[i];
    in.getline(name, i);
    d1.read(in);
    d2.read(in);
    in >> f[0] >> f[1] >> f[2];
  }
  void print() const {
    Data::print(name);
    d1.print();
    d2.print();
  }
};

int main() {
  {
    ofstream data("data.dat");
    assure(data, "data.dat");
    Conglomerate C("This is Conglomerate C",
      1.1, 2.2, 3.3, 4.4, 5.5,
      6.6, 7.7, 8.8, 9.9);
    cout << "C before storage" << endl;
    C.print();
    C.write(data);
  } // Closes file
  ifstream data("data.dat");
  assure(data, "data.dat");
  Conglomerate C;
  C.read(data);
  cout << "after storage: " << endl;
  C.print();
} ///:~
