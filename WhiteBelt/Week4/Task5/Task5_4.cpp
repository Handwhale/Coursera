// УЗНАТЬ КАК КРАСИВО ЧИТАТЬ ИЗ ПУСТОГО СТРИМА
// istream &operator>>(istream &stream, Rational &rational)
#include <iostream>
#include <sstream>
#include <string>

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
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4")
        {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal)
        {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct)
        {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}
