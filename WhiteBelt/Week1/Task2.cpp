// https://www.coursera.org/learn/c-plus-plus-white/programming/szG5X/minimal-naia-stroka
// Минимальная строка
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a, b, c;

    cin >> a >> b >> c;

    if (a < b)
    {
        if (a < c)
        {
            cout << a;
        }
        else
        {
            cout << c;
        }
    }
    else
    {
        if (b < c){
            cout << b;
        }
        else{
            cout << c;
        }
    }

    cout << a + b;
    return 0;
}