// Исключения в классе Rational
// https://www.coursera.org/learn/c-plus-plus-white/programming/7p79I/iskliuchieniia-v-klassie-rational
#include <iostream>
#include <exception>
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
        if (new_denominator == 0)
            throw invalid_argument("division by zero");

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

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    int new_denominator = lhs.Denominator() * rhs.Numerator();
    if (new_denominator == 0)
        throw domain_error("division by zero");
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

int main()
{
    try
    {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument &)
    {
    }

    try
    {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error &)
    {
    }

    cout << "OK" << endl;
    return 0;
}
