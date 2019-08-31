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

class Date
{
public:
    Date()
    {
        _year = 1;
        _month = 1;
        _day = 1;
    }

    Date(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
        ValidateMonth();
        ValidateDay();
    }

    int GetYear() const { return _year; };
    int GetMonth() const { return _month; };
    int GetDay() const { return _day; };

private:
    void ValidateMonth()
    {
        if (!(_month >= 1 && _month <= 12))
        {
            throw invalid_argument("Month value is invalid: " + to_string(_month));
        }
    }
    void ValidateDay()
    {
        if (!(_day >= 1 && _day <= 31))
        {
            throw invalid_argument("Day value is invalid: " + to_string(_day));
        }
    }
    int _year, _month, _day;
};

bool operator<(const Date &lhs, const Date &rhs)
{
    if (lhs.GetYear() != rhs.GetYear())
        return lhs.GetYear() < rhs.GetYear();

    if (lhs.GetMonth() != rhs.GetMonth())
        lhs.GetMonth() < rhs.GetMonth();

    return lhs.GetDay() < rhs.GetDay();
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setw(4) << date.GetYear() << '-'
           << setw(2) << date.GetMonth() << '-'
           << setw(2) << date.GetDay();

    return stream;
}

int ExtractValueFromDate(istream &ss)
{
    string result;

    if (ss.peek() == '-') // negative value
    {
        result += '-';
        ss.ignore();
    }

    char ch;
    ch = ss.peek();
    while (ch != '-' && ch != EOF) // EOF - End of file(stream)
    {

        if (isdigit(ch) || ch == '+')
        {
            result += ch;
            ss.ignore();
        }
        else
        {
            throw invalid_argument("Unexpected char value");
        }
        ch = ss.peek();
    }
    return stoi(result);
}

istream &operator>>(istream &is, Date &date)
{
    string data_input;
    is >> data_input;
    stringstream ss(data_input); // for storing wrong input

    int year, month, day;
    try
    {
        year = ExtractValueFromDate(ss);
        if (ss.peek() == '-')
            ss.ignore();
        else
            throw invalid_argument("Unexpected char value");

        month = ExtractValueFromDate(ss);
        if (ss.peek() == '-')
            ss.ignore();
        else
            throw invalid_argument("Unexpected char value");

        day = ExtractValueFromDate(ss);
    }
    catch (exception &ex)
    {
        throw invalid_argument("Wrong date format: " + data_input);
    }
    date = Date(year, month, day);
    return is;
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
        if (_data.count(date) == 0)
            return false;

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
        if (_data.count(date) == 0)
            return 0;
        _data.at(date);
        int n = _data[date].size();
        _data[date].clear();
        return n;
    }

    void Find(const Date &date) const
    {
        if (_data.count(date) == 0)
            return;
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
                    if (db.DeleteEvent(date_arg, event_arg))
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
        }
    }
    return 0;
}
