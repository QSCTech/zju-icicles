//: C02:Date.cpp {O}
// From "Thinking in C++, 2nd Edition, Volume 2"
// by Bruce Eckel & Chuck Allison, (c) 2001 MindView, Inc.
// Available at www.BruceEckel.com.
#include "Date.h"
#include <string>
#include <algorithm> // for swap()
#include <ctime>
#include <cassert>
#include <sstream>
#include <iomanip>
using namespace std;

namespace {
  const int daysInMonth[][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}};
  inline bool isleap(int y) {
    return y%4 == 0 && y%100 != 0 || y%400 == 0;
  }
}

Date::Date() {
  // Get current date
  time_t tval = time(0);
  struct tm *now = localtime(&tval);
  year = now->tm_year + 1900;
  month = now->tm_mon + 1;
  day = now->tm_mday;
}

Date::Date(int yr, int mon, int dy) {
  assert(1 <= mon && mon <= 12);
  assert(1 <= dy && 
    dy <= daysInMonth[isleap(year)][mon]);
  year = yr;
  month = mon;
  day = dy;
}

Date::Date(const std::string& s) {
  // Assume YYYYMMDD format
  istringstream is(s);
  is >> setw(4) >> year;
  is >> setw(2) >> month;
  is >> setw(2) >> day;
}

int Date::getYear() const {
  return year;
}

int Date::getMonth() const {
  return month;
}

int Date::getDay() const {
  return day;
}

string Date::toString() const {
  ostringstream os;
  os << setw(4) << year
   << setw(2) << month
   << setw(2) << day;
  return os.str();
}

int Date::compare(const Date& d2) const {
  int result = year - d2.year;
  if (result == 0) {
    result = month - d2.month;
    if (result == 0)
      result = day - d2.day;
  }
  return result;   
}

int Date::daysInPrevMonth(int year, int month) {
  if (month == 1) {
    --year;
    month = 12;
  }
  else
    --month;
  return daysInMonth[isleap(year)][month];
}

bool operator<(const Date& d1, const Date& d2) {
  return d1.compare(d2) < 0;
}
bool operator<=(const Date& d1, const Date& d2) {
  return d1.compare(d2) <= 0;
}
bool operator>(const Date& d1, const Date& d2) {
  return d1.compare(d2) >= 0;
}
bool operator>=(const Date& d1, const Date& d2) {
  return d1.compare(d2) >= 0;
}
bool operator==(const Date& d1, const Date& d2) {
  return d1.compare(d2) == 0;
}
bool operator!=(const Date& d1, const Date& d2) {
  return d1.compare(d2) != 0;
}

Duration 
duration(const Date& date1, const Date& date2) {
  int y1 = date1.year;
  int y2 = date2.year;
  int m1 = date1.month;
  int m2 = date2.month;
  int d1 = date1.day;
  int d2 = date2.day;

  // Compute the compare
  int order = date1.compare(date2);
  if (order == 0)
    return Duration(0,0,0);
  else if (order > 0) {
    // Make date1 precede date2 locally
    using std::swap;
    swap(y1, y2);
    swap(m1, m2);
    swap(d1, d2);
  }

  int years = y2 - y1;
  int months = m2 - m1;
  int days = d2 - d1;
  assert(years > 0 ||
     years == 0 && months > 0 ||
     years == 0 && months == 0 && days > 0);

  // Do the obvious corrections (must adjust days
  // before months!) - This is a loop in case the
  // previous month is February, and days < -28.
  int lastMonth = m2;
  int lastYear = y2;
  while (days < 0) {
    // Borrow from month
    assert(months > 0);
    days += Date::daysInPrevMonth(
      lastYear, lastMonth--);
    --months;
  }

  if (months < 0) {
    // Borrow from year
    assert(years > 0);
    months += 12;
    --years;
  }
  return Duration(years, months, days);
} ///:~
