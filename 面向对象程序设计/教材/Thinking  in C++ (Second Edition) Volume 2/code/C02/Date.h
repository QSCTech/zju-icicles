//: C02:Date.h
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#ifndef DATE_H
#define DATE_H
#include <string>

struct Duration {
  int years;
  int months;
  int days;
  Duration(int y, int m, int d)
    : years(y), months(m), days(d) {}
};

class Date {
public:
  Date();
  Date(int year, int month, int day);
  Date(const std::string&);
  int getYear() const;
  int getMonth() const;
  int getDay() const;
  std::string toString() const;
  friend Duration 
  duration(const Date&, const Date&);
  friend bool 
  operator<(const Date&, const Date&);
  friend bool 
  operator<=(const Date&, const Date&);
  friend bool 
  operator>(const Date&, const Date&);
  friend bool 
  operator>=(const Date&, const Date&);
  friend bool 
  operator==(const Date&, const Date&);
  friend bool 
  operator!=(const Date&, const Date&);
private:
  int year;
  int month;
  int day;
  int compare(const Date&) const;
  static int daysInPrevMonth(int year,int mon);
};
#endif ///:~
