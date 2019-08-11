#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
    os << "{";
    bool first = true;
    for (const auto &kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception &e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name);
    void ChangeLastName(int year, const string &last_name);
    string GetFullName(int year);
};

void SimpleTests()
{
    Person person;

    AssertEqual(person.GetFullName(1), "Incognito");

    person.ChangeFirstName(10, "Polina");
    AssertEqual(person.GetFullName(1), "Incognito");
    AssertEqual(person.GetFullName(10), "Polina with unknown last name");
    AssertEqual(person.GetFullName(11), "Polina with unknown last name");

    person.ChangeLastName(20, "Sergeevna");
    AssertEqual(person.GetFullName(1), "Incognito");
    AssertEqual(person.GetFullName(10), "Polina with unknown last name");
    AssertEqual(person.GetFullName(11), "Polina with unknown last name");
    AssertEqual(person.GetFullName(20), "Polina Sergeevna");
    AssertEqual(person.GetFullName(21), "Polina Sergeevna");

    person.ChangeFirstName(15, "Appolinaria");
    AssertEqual(person.GetFullName(1), "Incognito");
    AssertEqual(person.GetFullName(10), "Polina with unknown last name");
    AssertEqual(person.GetFullName(11), "Polina with unknown last name");
    AssertEqual(person.GetFullName(15), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(16), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(20), "Appolinaria Sergeevna");
    AssertEqual(person.GetFullName(21), "Appolinaria Sergeevna");

    person.ChangeLastName(30, "Volkova");
    AssertEqual(person.GetFullName(1), "Incognito");
    AssertEqual(person.GetFullName(10), "Polina with unknown last name");
    AssertEqual(person.GetFullName(11), "Polina with unknown last name");
    AssertEqual(person.GetFullName(15), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(16), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(20), "Appolinaria Sergeevna");
    AssertEqual(person.GetFullName(21), "Appolinaria Sergeevna");
    AssertEqual(person.GetFullName(30), "Appolinaria Volkova");
    AssertEqual(person.GetFullName(31), "Appolinaria Volkova");
}

void BackwardInsertNameTest()
{
    Person person;

    person.ChangeFirstName(10, "Polina");
    person.ChangeFirstName(5, "Appolinaria");

    AssertEqual(person.GetFullName(1), "Incognito");
    AssertEqual(person.GetFullName(5), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(7), "Appolinaria with unknown last name");
    AssertEqual(person.GetFullName(10), "Polina with unknown last name");
}

void BackwardInsertLastNameTest()
{
    Person person;

    person.ChangeLastName(10, "Sergeeva");
    person.ChangeLastName(5, "Volkova");

    AssertEqual(person.GetFullName(1), "Incognito");
    AssertEqual(person.GetFullName(5), "Volkova with unknown first name");
    AssertEqual(person.GetFullName(7), "Volkova with unknown first name");
    AssertEqual(person.GetFullName(10), "Sergeeva with unknown first name");
}

int main()
{
    TestRunner runner;
    runner.RunTest(SimpleTests, "Simple class tests");
    runner.RunTest(BackwardInsertNameTest, "First name insert backward");
    runner.RunTest(BackwardInsertLastNameTest, "Last name insert backward");
    return 0;
}
