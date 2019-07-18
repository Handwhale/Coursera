// Наибольший общий делитель
// https://www.coursera.org/learn/c-plus-plus-white/programming/YhvR9/naibol-shii-obshchii-dielitiel
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
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
    cout << a + b;

    return 0;
}