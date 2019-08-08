// Калькулятор обыкновенных дробей
// https://www.coursera.org/learn/c-plus-plus-white/programming/bshor/kal-kuliator-obyknoviennykh-drobiei
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
            throw invalid_argument("Invalid argument");

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

Rational AddSubBase(const Rational &lhs, const Rational &rhs, bool is_add)
{
    int add_or_sub_coef = is_add ? 1 : -1;
    int lhs_denom = lhs.Denominator();
    int rhs_denom = rhs.Denominator();
    if (lhs_denom == rhs_denom)
    {
        return Rational(lhs.Numerator() + rhs.Numerator() * add_or_sub_coef, lhs_denom);
    }
    else
    {
        return Rational(lhs.Numerator() * rhs_denom + rhs.Numerator() * lhs_denom * add_or_sub_coef, rhs_denom * lhs_denom);
    }
}

Rational operator+(const Rational &lhs, const Rational &rhs)
{
    return AddSubBase(lhs, rhs, true);
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
    return AddSubBase(lhs, rhs, false);
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    int new_denominator = lhs.Denominator() * rhs.Numerator();

    if (new_denominator == 0)
        throw domain_error("Division by zero");

    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

Rational operator*(const Rational &lhs, const Rational &rhs)
{
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

ostream &operator<<(ostream &stream, const Rational &rational)
{
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}

istream &operator>>(istream &stream, Rational &rational)
{
    int num, denum;

    if (stream)
    {
        stream >> num;
    }
    else
        return stream;

    stream.ignore(1);

    if (stream)
    {
        stream >> denum;
    }
    else
        return stream;

    rational = Rational(num, denum);

    return stream;
}

int main()
{
    Rational a, b;
    char operation;

    try
    {
        cin >> a >> operation >> b;
        switch (operation)
        {
        case '+':
            cout << a + b;
            break;

        case '-':
            cout << a - b;
            break;

        case '*':
            cout << a * b;
            break;

        case '/':
            cout << a / b;
            break;
        }
        return 0;
    }
    catch (exception &ex)
    {
        cout << ex.what();
    }
}

// 1/2 + 1/3

// 1/2 + 5/0

// 4/5 / 0/8