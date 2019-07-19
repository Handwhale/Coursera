#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational
{
public:
    Rational()
    {
        numerator = 0;
        denominator = 1;
        is_negative = false;
    }

    Rational(int new_numerator, int new_denominator)
    {

        if ((new_numerator < 0 && new_denominator > 0) ||
            (new_denominator < 0 && new_numerator > 0))
        {
            is_negative = true;
        }
        else
        {
            is_negative = false;
        }

        new_denominator = abs(new_denominator);
        new_numerator = abs(new_numerator);

        if (new_numerator == 0)
        {
            new_denominator = 1;
        }

        numerator = new_numerator;
        denominator = new_denominator;
        RationalFit();
    }

    int Numerator() const
    {
        if (is_negative)
            return -numerator;
        else
            return numerator;
    }

    int Denominator() const
    {
        return denominator;
    }

private:
    int EuclideanAlgorithm(int a, int b)
    {
        while (a > 0 && b > 0)
        {
            if (a > b)
            {
                a %= b;
            }
            else
            {
                b %= a;
            }
        }
        return a + b;
    }
    void RationalFit()
    {
        int divider = EuclideanAlgorithm(numerator, denominator);
        numerator /= divider;
        denominator /= divider;
    }

    int numerator, denominator;
    bool is_negative;
};

bool operator==(const Rational &lhs, const Rational &rhs)
{
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<(const Rational &lhs, const Rational &rhs)
{
    int lhs_num = lhs.Numerator();
    int rhs_num = rhs.Numerator();
    int lhs_denom = lhs.Denominator();
    int rhs_denom = rhs.Denominator();

    if (rhs_denom == lhs_denom)
    {
        return lhs_num < rhs_num;
    }
    else
    {
        if (lhs_num * rhs_denom < rhs_num * lhs_denom)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int main()
{
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3)
        {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs)
        {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}})
        {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2)
        {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
