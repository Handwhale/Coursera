// Тесты для функции IsPalindrom
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/Jzr59/tiesty-dlia-funktsii-ispalindrom
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

bool IsPalindrom(const string &str);

void BoundaryCases()
{
    Assert(IsPalindrom(""), "Empty string");
    Assert(IsPalindrom("v"), "One char string");
    Assert(IsPalindrom(" "), "One space char string");
    Assert(IsPalindrom("        "), "Space string");
    Assert(IsPalindrom("."), "One special char string");
}

void EvenCases()
{
    Assert(IsPalindrom("qwwq"), "Even case #1");
    Assert(IsPalindrom("qw  wq"), "Even case #2");
    Assert(IsPalindrom("ZxCvvCxZ"), "Even case #3");
    Assert(IsPalindrom("Z x Cv  vC x Z"), "Even case #4");
    Assert(!IsPalindrom("Z x CV  vC x Z"), "Even case #5");
    Assert(!IsPalindrom("xyYX"), "Even case #6");
}

void OddCases()
{
    Assert(IsPalindrom("madam"), "Odd case #1");
    Assert(IsPalindrom("ma am"), "Odd case #2");
    Assert(!IsPalindrom("wrong"), "Odd case #3");
}

void SpecialCharters()
{
    Assert(IsPalindrom("*/ /*"), "SpecialCharter #1");
    Assert(IsPalindrom("#$ $#"), "SpecialCharter #2");
    Assert(IsPalindrom("@!!@"), "SpecialCharter #3");
    Assert(!IsPalindrom("(^**^)"), "SpecialCharter #4");
    Assert(!IsPalindrom("(^*/*^)"), "SpecialCharter #5");
    Assert(IsPalindrom("-+-"), "SpecialCharter #6");

    Assert(!IsPalindrom("+-"), "SpecialCharter #7");
    Assert(!IsPalindrom("%*"), "SpecialCharter #8");
    Assert(!IsPalindrom("()"), "SpecialCharter #9");
    Assert(IsPalindrom("\n"), "SpecialCharter #10");
}

void SpaceCase(){
    Assert(IsPalindrom(" q "), "SpaceCase #2");
    Assert(IsPalindrom("  q  "), "SpaceCase #3");
    Assert(IsPalindrom("qw     wq"), "SpaceCase #4");
    Assert(!IsPalindrom(" q we   ew q"), "SpaceCase #5");
    Assert(!IsPalindrom("q w ee  w  q"), "SpaceCase #6");
}

void RunAllTests()
{
    TestRunner runner;
    runner.RunTest(BoundaryCases, "BoundaryCases");
    runner.RunTest(EvenCases, "EvenCases");
    runner.RunTest(OddCases, "OddCases");
    runner.RunTest(SpecialCharters, "SpecialCharters");
    runner.RunTest(SpaceCase, "SpaceCase");
}

int main()
{
    RunAllTests();
    return 0;
}
