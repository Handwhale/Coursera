// https://www.coursera.org/learn/c-plus-plus-white/programming/SqolV/faktorial
// Факториал
#include <iostream>
#include <cmath>

using namespace std;

int Factorial(int value){
    if (value <= 1)
        return 1;
    else
        return value * Factorial(value - 1); 
}

int main()
{
    int a;
    cin >> a; 
    cout << Factorial(a);
    return 0;
}
