#include "date.h"
#include <ostream>
#include <iostream>
#include <fstream>

using namespace std;

Date::~Date() {}

Date::Date() : year(0), month(0), day(0) {}

Date::Date(unsigned int y, unsigned int m, unsigned int d) : day(d), month(m), year(y) {}


Date::Date(const Date &d) {
    day = d.day;
    month = d.month;
    year = d.year;
}

unsigned int Date::getYear() const {
    return year;
}

void Date::setYear(unsigned int y) {
    year = y;
}

unsigned int Date::getMonth() const {
    return month;
}

void Date::setMonth(unsigned int m) {
    month = m;
}

unsigned int Date::getDay() const {
    return day;
}

void Date::setDay(unsigned int d) {
    day = d;
}

int Date::countLeapYears() const{
    int years = year;
    if (month <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

Date & Date::operator=(const Date &d1) {
    this->day = d1.day;
    this->month = d1.month;
    this->year = d1.year;
    return *this;
}

bool Date::operator<(const Date &d) const {
    if (this->year < d.year) { return true; }
    if (this->year == d.year && this->month < d.month) { return true; }
    if (this->year == d.year && this->month == d.month && this->day < d.day) { return true; }
    return false;
}

bool Date::operator==(const Date &d) const {
    if (this->year == d.year && this->month == d.month && this->day == d.day) { return true; }
    return false;
}

int Date::operator-(const Date &d) const {
    int days1 = this->year * 365 + this->day;
    for (int i = 0; i < this->month - 1; i++)
        days1 += monthDays[i];
    days1 += countLeapYears();

    int days2 = d.year * 365 + d.day;
    for (int i = 0; i < d.month - 1; i++)
        days2 += monthDays[i];
    days2 += d.countLeapYears();

    int days = days1 - days2;
    return days;
}

bool isLeap(unsigned int y)
{
    if (y%100 != 0 && y%4 == 0 || y %400 == 0)
        return true;

    return false;
}

int offsetDays(unsigned int d, unsigned int m, unsigned int y)
{
    int off = d;

    switch (m - 1)
    {
        case 11:
            off += 30;
        case 10:
            off += 31;
        case 9:
            off += 30;
        case 8:
            off += 31;
        case 7:
            off += 31;
        case 6:
            off += 30;
        case 5:
            off += 31;
        case 4:
            off += 30;
        case 3:
            off += 31;
        case 2:
            off += 28;
        case 1:
            off += 31;
    }

    if (isLeap(y) && m > 2)
        off += 1;

    return off;
}

void revoffsetDays(unsigned int off, unsigned int y, unsigned int *d, unsigned int *m)
{
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31 };

    if (isLeap(y))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (off <= month[i])
            break;
        off = off - month[i];
    }

    *d = off;
    *m = i;
}



Date operator+(Date &d, int x){
    unsigned int off1 = offsetDays(d.day, d.month, d.year);
    unsigned int rdays = isLeap(d.year)?(366-off1):(365-off1);

    // y2 is going to store result year and
    // offset2 is going to store offset days
    // in result year.
    int y2, off2;
    if (x <= rdays)
    {
        y2 = d.year;
        off2 = off1 + x;
    }

    else
    {
        // x may store thousands of days.
        // We find correct year and offset
        // in the year.
        x -= rdays;
        y2 = d.year + 1;
        int y2days = isLeap(y2)?366:365;
        while (x >= y2days)
        {
            x -= y2days;
            y2++;
            y2days = isLeap(y2)?366:365;
        }
        off2 = x;
    }

    // Find values of day and month from
    // offset of result year.
    unsigned int m2, d2;
    revoffsetDays(off2, y2, &d2, &m2);
    return Date(y2,m2,d2);
}

void Date::print() const {
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

void Date::print(std::stringstream &ss) const {
    ss << "Date: " << year << "/" << month << "/" << day;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    std::stringstream ss;
    date.print(ss);
    os<<ss.str();
    return os;
}

std::istream& operator>>(std::istream &is, Date& obj){
    unsigned int y, m, d;
    is >> y >> m >> d;
    Date date(y,m,d);
    obj = date;
    return is;
}

void Date::saveDate(std::ofstream &ofs) const {
    ofs << year << ' ' << month << ' ' << day;
}
