#include "date.h"
#include <iomanip>

using namespace std;

Date::Date(int year, int month, int day) {
    _year = year;
    _month = month;
    _day = day;
}

int Date::GetYear() const { return _year; }

int Date::GetMonth() const { return _month; }

int Date::GetDay() const { return _day; }

std::tuple<int, int, int> Date::GetTuple() const {
    return make_tuple(_year, _month, _day);
}

ostream &operator<<(ostream &os, const Date &data) {
    os << setfill('0');
    os << setw(4) << data.GetYear() << '-'
       << setw(2) << data.GetMonth() << '-'
       << setw(2) << data.GetDay();

    return os;
}


Date ParseDate(std::istream &is) {
    int year, month, day;
    is >> year;
    is.ignore();

    is >> month;
    is.ignore();

    is >> day;

    return Date(year, month, day);
}


bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.GetTuple() == rhs.GetTuple();
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return lhs.GetTuple() != rhs.GetTuple();
}

bool operator<(const Date &lhs, const Date &rhs) {
    return lhs.GetTuple() < rhs.GetTuple();
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return lhs.GetTuple() <= rhs.GetTuple();
}

bool operator>(const Date &lhs, const Date &rhs) {
    return lhs.GetTuple() > rhs.GetTuple();
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return lhs.GetTuple() >= rhs.GetTuple();
}

