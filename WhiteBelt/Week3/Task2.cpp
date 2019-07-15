// https://www.coursera.org/learn/c-plus-plus-white/programming/zqw0h/sortirovka-biez-uchiota-rieghistra
// Сортировка без учёта регистра
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    string value;
    vector<string> array;

    cin >> n;

    for (auto i = 0; i < n; i++)
    {
        cin >> value;
        array.push_back(value);
    }

    sort(array.begin(), array.end(),
         [](const string &lhs, const string &rhs) {
             if (tolower(lhs[0]) < tolower(rhs[0]))
                 return true;
             else
                 return false;
         });

    for (const auto &i : array)
    {
        cout << i << ' ';
    }

    return 0;
}