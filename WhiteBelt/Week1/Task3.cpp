// https://www.coursera.org/learn/c-plus-plus-white/programming/jRy5s/uravnieniie
// Уравнение
#include <iostream>
#include <cmath>

using namespace std;

// check two zero case
int main()
{
    float a, b, c, d_sqrt;

    cin >> a >> b >> c;

    d_sqrt = sqrt(b * b - 4 * a * c);

    if (a == 0)
    {
        if (b == 0) // c != 0
        {
            // no roots
            return 0;
        }
        else
        {
            cout << -c / b;
        }
    }

    else if (b == 0 && c == 0)
    {
        cout << 0;
    }

    else if (d_sqrt > 0)
    {
        cout << (-b - d_sqrt) / (2 * a)
             << ' '
             << (-b + d_sqrt) / (2 * a);
    }
    else if (d_sqrt == 0)
    {
        cout << -b / (2 * a);
    }

    return 0;
}
