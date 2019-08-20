// Часть вектора
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/CzFMg/chast-viektora
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int> &numbers)
{
    auto f_res = find_if(numbers.begin(), numbers.end(), [](auto x) { return x < 0 ? true : false; });
    for(auto i = f_res; i != begin(numbers); i){
        cout << *(--i) << ' ';
    }
}

int main()
{
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4}); // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}