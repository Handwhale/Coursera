#pragma once
#include <iostream>

class Date {
public:
    Date(int year, int month, int day);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;
    // Test for change tuple values
    std::tuple<int, int, int> GetTuple() const;

private:
    int _year, _month, _day;
};

std::ostream &operator<<(std::ostream &os, const Date &data);

bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);


Date ParseDate(std::istream &is);