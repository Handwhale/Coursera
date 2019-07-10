// https://www.coursera.org/learn/c-plus-plus-white/programming/jRy5s/uravnieniie
// Уравнение
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float a, b, c, d_sqrt;

    cin >> a >> b >> c;

    d_sqrt = sqrt(b * b - 4 * a * c);

    if (a == 0){
        cout << -c/b;
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
