//: C11:Observer.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
// The Observer interface
#ifndef OBSERVER_H
#define OBSERVER_H

class Observable;
class Argument {};

class Observer {
public:
  // Called by the observed object, whenever 
  // the observed object is changed:
  virtual void 
  update(Observable* o, Argument * arg) = 0;
};
#endif // OBSERVER_H ///:~
