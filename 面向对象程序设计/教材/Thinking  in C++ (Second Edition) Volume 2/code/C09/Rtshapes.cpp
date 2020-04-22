//: C09:Rtshapes.cpp
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// Counting shapes
//{L} ../TestSuite/Test
#include "../purge.h"
#include <iostream>
#include <ctime>
#include <typeinfo>
#include <vector>
using namespace std;

class Shape {
protected:
  static int count;
public:
  Shape() { count++; }
  virtual ~Shape() { count--; }
  virtual void draw() const = 0;
  static int quantity() { return count; }
};

int Shape::count = 0;

class SRectangle : public Shape {
  void operator=(SRectangle&); // Disallow
protected:
  static int count;
public:
  SRectangle() { count++; }
  SRectangle(const SRectangle&) { count++;}
  ~SRectangle() { count--; }
  void draw() const {
    cout << "SRectangle::draw()" << endl;
  }
  static int quantity() { return count; }
};

int SRectangle::count = 0;

class SEllipse : public Shape {
  void operator=(SEllipse&); // Disallow
protected:
  static int count;
public:
  SEllipse() { count++; }
  SEllipse(const SEllipse&) { count++; }
  ~SEllipse() { count--; }
  void draw() const {
    cout << "SEllipse::draw()" << endl;
  }
  static int quantity() { return count; }
};

int SEllipse::count = 0;

class SCircle : public SEllipse {
  void operator=(SCircle&); // Disallow
protected:
  static int count;
public:
  SCircle() { count++; }
  SCircle(const SCircle&) { count++; }
  ~SCircle() { count--; }
  void draw() const {
    cout << "SCircle::draw()" << endl;
  }
  static int quantity() { return count; }
};

int SCircle::count = 0;

int main() {
  vector<Shape*> shapes;
  srand(time(0)); // Seed random number generator
  const int mod = 12;
  // Create a random quantity of each type:
  for(int i = 0; i < rand() % mod; i++)
    shapes.push_back(new SRectangle);
  for(int j = 0; j < rand() % mod; j++)
    shapes.push_back(new SEllipse);
  for(int k = 0; k < rand() % mod; k++)
    shapes.push_back(new SCircle);
  int nCircles = 0;
  int nEllipses = 0;
  int nRects = 0;
  int nShapes = 0;
  for(int u = 0; u < shapes.size(); u++) {
    shapes[u]->draw();
    if(dynamic_cast<SCircle*>(shapes[u]))
      nCircles++;
    if(dynamic_cast<SEllipse*>(shapes[u]))
      nEllipses++;
    if(dynamic_cast<SRectangle*>(shapes[u]))
      nRects++;
    if(dynamic_cast<Shape*>(shapes[u]))
      nShapes++;
  }
  cout << endl << endl
    << "Circles = " << nCircles << endl
    << "Ellipses = " << nEllipses << endl
    << "Rectangles = " << nRects << endl
    << "Shapes = " << nShapes << endl
    << endl
    << "SCircle::quantity() = "
    << SCircle::quantity() << endl
    << "SEllipse::quantity() = "
    << SEllipse::quantity() << endl
    << "SRectangle::quantity() = "
    << SRectangle::quantity() << endl
    << "Shape::quantity() = "
    << Shape::quantity() << endl;
  purge(shapes);
} ///:~
