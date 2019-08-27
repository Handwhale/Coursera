// Финальная задача курса
// https://www.coursera.org/learn/c-plus-plus-white/programming/sO7Vq/final-naia-zadacha-kursa
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <algorithm>
#include <iomanip>

using namespace std;

// Delete с неверной датой попадает в исключение, но возможно неправильно выводит сообщение.

class Date
{
public:
    Date()
    {
        _year = 1;
        _month = 1;
        _day = 1;
    }

    Date(string year, string month, string day)
    {
        _year = stoi(year);
        _month = stoi(month);
        if (!(_month >= 1 && _month <= 12))
        {
            throw invalid_argument("Month value is invalid: " + to_string(_month));
        }
        _day = stoi(day);
        if (!(_day >= 1 && _day <= 31))
        {
            throw invalid_argument("Day value is invalid: " + to_string(_day));
        }
    }

    int GetYear() const { return _year; };
    int GetMonth() const { return _month; };
    int GetDay() const { return _day; };

private:
    int _year, _month, _day;
};

bool operator<(const Date &lhs, const Date &rhs)
{
    if (lhs.GetYear() < rhs.GetYear())
        return true;

    if (lhs.GetMonth() < rhs.GetMonth())
        return true;

    if (lhs.GetDay() < rhs.GetDay())
        return true;

    return false;
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setfill('0');
    stream << setw(4) << date.GetYear() << '-'
           << setw(2) << date.GetMonth() << '-'
           << setw(2) << date.GetDay();

    return stream;
}

bool IsFirstCharMinus(istringstream &stream)
{
    // first place - may means negative value
    if (stream.peek() == '-')
    {
        stream.ignore(1);
        return true;
    }
    else
        return false;
}

istringstream &operator>>(istringstream &stream, Date &date)
{
    string year, month, day, value;
    if (IsFirstCharMinus(stream))
    {
        year += '-';
    }
    getline(stream, value, '-');
    year += value;

    if (IsFirstCharMinus(stream))
    {
        month += '-';
    }
    getline(stream, value, '-');
    month += value;

    if (IsFirstCharMinus(stream))
    {
        day += '-';
    }
    getline(stream, value, ' ');
    day += value;

    int int_year, int_month, int_day;
    try
    {
        int_year = stoi(year);
        int_month = stoi(month);
        int_day = stoi(day);
    }
    catch (exception &ex)
    {
        throw invalid_argument("Wrong date format: " +
                               year + '-' + month + '-' + day);
    }

    date = Date(year, month, day);

    return stream;
}

class Database
{
public:
    void AddEvent(const Date &date, const string &event)
    {
        _data[date].insert(event);
    }
    bool DeleteEvent(const Date &date, const string &event)
    {
        auto event_set = _data.at(date);

        auto find_result = find(_data[date].begin(), _data[date].end(), event);
        if (find_result != _data[date].end())
        {
            _data[date].erase(find_result);
            return true;
        }
        else
        {
            return false;
        }
    }
    int DeleteDate(const Date &date)
    {
        set<string> &event_set = _data.at(date);
        int n = event_set.size();
        event_set.clear();
        return n;
    }

    void Find(const Date &date) const
    {
        for (const auto &item : _data.at(date))
        {
            cout << item << endl;
        }
    }

    void Print() const
    {
        for (const auto &pair : _data)
        {
            for (const auto &event : pair.second)
            {
                cout << pair.first << ' ' << event << endl;
            }
        }
    }

private:
    map<Date, set<string>> _data;
};

void DateCheck()
{
    {
        // корректная дата
        string input = "1-1-1";
        istringstream ss(input);
        Date date;
        ss >> date;
        cerr << date << " and " << input << endl;
    }

    {
        // TODO
        // корректная дата
        string input = "-1-1-1";
        istringstream ss(input);
        Date date;
        ss >> date;
        cerr << date << " and " << input << endl;
    }

    {
        string input = "1--1-1";
        istringstream ss(input);
        Date date;
        try
        {
            ss >> date;
        }
        catch (invalid_argument &ex)
        {
            cerr << ex.what() << " OK" << endl;
        }
    }

    {
        string input = "1---1-1";
        istringstream ss(input);
        Date date;
        try
        {
            ss >> date;
        }
        catch (invalid_argument &ex)
        {
            cerr << ex.what() << " OK" << endl;
        }
    }
    {
        // корректная дата
        string input = "1​-+1-+1";
        istringstream ss(input);
        Date date;
        ss >> date;
        cerr << date << " and " << input << endl;
    }
    {
        // корректная дата
        string input = "1​-+1-32";
        istringstream ss(input);
        Date date;
        try
        {
            ss >> date;
        }
        catch (invalid_argument &ex)
        {
            cerr << ex.what() << " OK" << endl;
        }
    }
}

int main()
{
    Database db;
    string input_line;
    while (getline(cin, input_line))
    {
        try
        {
            if (input_line.length() == 0)
                continue; // empty string evade
            istringstream iss(input_line);
            string command;
            iss >> command;
            if (command == "Add")
            {
                Date date_arg;
                string event_arg;
                iss >> date_arg >> event_arg;

                db.AddEvent(date_arg, event_arg);
                continue;
            }
            if (command == "Del")
            {
                Date date_arg;
                string event_arg;
                iss >> date_arg >> event_arg;

                if (event_arg.length() == 0)
                {
                    auto deleted_events = db.DeleteDate(date_arg);
                    cout << "Deleted " << deleted_events << " events" << endl;
                }
                else
                {
                   vector check if contains if (db.DeleteEvent(date_arg, event_arg))
                    {
                        cout << "Deleted successfully" << endl;
                    }
                    else
                    {
                        cout << "Event not found" << endl;
                    }
                }
                continue;
            }
            if (command == "Find")
            {
                Date date_arg;
                iss >> date_arg;
                db.Find(date_arg);
                continue;
            }
            if (command == "Print")
            {
                db.Print();
                continue;
            }
            throw invalid_argument("Unknown command: " + command);
        }
        catch (exception &ex)
        {
            cout << ex.what() << endl;
            return 0;
        }
    }
    return 0;
}
