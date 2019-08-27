#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string ParseEvent(istream &is) {
    string line;
    getline(is, line);

    auto word_start_it = find_if(line.begin(), line.end(), [](const char &ch) { return ch != ' '; });
    return string(word_start_it, line.end());
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void MainSolutionTest(istream &cin, ostream &cout) {
    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }
}

void TestParseEvent() {
    {
        istringstream is("");
        AssertEqual(ParseEvent(is), "", "Parse empty event");
    }
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestCourseraInput() {
    {
        istringstream is("Add 2017-06-01 1st of June\n"
                         "Add 2017-07-08 8th of July\n"
                         "Add 2017-07-08 Someone's birthday\n"
                         "Del date == 2017-07-08");

        ostringstream result;
        MainSolutionTest(is, result);
        AssertEqual(result.str(), "Removed 2 entries\n", "Del Example");
    }
    {
        istringstream is("Add 2017-01-01 Holiday\n"
                         "Add 2017-03-08 Holiday\n"
                         "Add 2017-1-1 New Year\n"
                         "Add 2017-1-1 New Year\n"
                         "Print");

        ostringstream result;
        string expected = "2017-01-01 Holiday\n"
                          "2017-01-01 New Year\n"
                          "2017-03-08 Holiday\n";
        MainSolutionTest(is, result);
        AssertEqual(result.str(), expected, "Print Example");
    }
    {
        istringstream is("Add 2017-01-01 Holiday\n"
                         "Add 2017-03-08 Holiday\n"
                         "Add 2017-01-01 New Year\n"
                         "Find event != \"working day\"\n"
                         "Add 2017-05-09 Holiday");

        ostringstream result;
        string expected = "2017-01-01 Holiday\n"
                          "2017-01-01 New Year\n"
                          "2017-03-08 Holiday\n"
                          "Found 3 entries\n";
        MainSolutionTest(is, result);
        AssertEqual(result.str(), expected, "Find Example");
    }
    {
        istringstream is("Add 2017-01-01 New Year\n"
                         "Add 2017-03-08 Holiday\n"
                         "Add 2017-01-01 Holiday\n"
                         "Last 2016-12-31\n"
                         "Last 2017-01-01\n"
                         "Last 2017-06-01\n"
                         "Add 2017-05-09 Holiday\n");

        ostringstream result;
        string expected = "No entries\n"
                          "2017-01-01 Holiday\n"
                          "2017-03-08 Holiday\n";
        MainSolutionTest(is, result);
        auto r = result.str();
        AssertEqual(r, expected, "Find Example");
    }
    {
        istringstream is("Add 2017-11-21 Tuesday\n"
                         "Add 2017-11-20 Monday\n"
                         "Add 2017-11-21 Weekly meeting\n"
                         "Print\n"
                         "Find event != \"Weekly meeting\"\n"
                         "Last 2017-11-30\n"
                         "Del date > 2017-11-20\n"
                         "Last 2017-11-30\n"
                         "Last 2017-11-01");

        ostringstream result;
        string expected = "2017-11-20 Monday\n"
                          "2017-11-21 Tuesday\n"
                          "2017-11-21 Weekly meeting\n" // print end
                          "2017-11-20 Monday\n"
                          "2017-11-21 Tuesday\n"
                          "Found 2 entries\n"   // find end
                          "2017-11-21 Weekly meeting\n" // Last end
                          "Removed 2 entries\n" // Del end
                          "2017-11-20 Monday\n" // last end
                          "No entries\n";       // last end
        MainSolutionTest(is, result);
        AssertEqual(result.str(), expected, "Find Example");
    }
};

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestCourseraInput, "TestCourseraInput");
}
