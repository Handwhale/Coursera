// Тесты для класса Rational
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/KJ7Sh/tiesty-dlia-klassa-rational
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// ЗАКОМЕНТЬ КЛАССС RATIONAL

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

class Rational
{
public:
    Rational(){}
    Rational(int numerator, int denominator)
    {
    }

    int Numerator() const
    {
        return 1;
    }

    int Denominator() const
    {
        return 1;
    }
};

void DefaultConstructorTest()
{
    // Default constructor
    Rational rat1;
    Rational rat2(0, 1);
    AssertEqual(rat1.Numerator(), rat2.Numerator());
    AssertEqual(rat1.Denominator(), rat2.Denominator());
}

void ReductionCaseTest()
{
    // Reduction case
    Rational rat1(24, 6);
    AssertEqual(rat1.Numerator(), 4);
    AssertEqual(rat1.Denominator(), 1);

    rat1 = Rational(15, 20);
    AssertEqual(rat1.Numerator(), 3);
    AssertEqual(rat1.Denominator(), 4);
}

void NegativeValueTest()
{
    // Negative value case
    Rational rat1(-1, 2);
    AssertEqual(rat1.Numerator(), -1);
    AssertEqual(rat1.Denominator(), 2);

    rat1 = Rational(1, -2);
    AssertEqual(rat1.Numerator(), -1);
    AssertEqual(rat1.Denominator(), 2);

    rat1 = Rational(-1, -2);
    AssertEqual(rat1.Numerator(), 1);
    AssertEqual(rat1.Denominator(), 2);
}

void ZeroNumeratorTest()
{
    // Zero Numerator
    Rational rat1(0, 256);
    AssertEqual(rat1.Numerator(), 0);
    AssertEqual(rat1.Denominator(), 1);
}

void AllTests()
{
    TestRunner runner;
    runner.RunTest(DefaultConstructorTest, "Default constructor test");
    runner.RunTest(ReductionCaseTest, "Reduction case test");
    runner.RunTest(NegativeValueTest, "Negative value test");
    runner.RunTest(ZeroNumeratorTest, "Zero numerator test");
}

int main()
{
    AllTests();
    return 0;
}
