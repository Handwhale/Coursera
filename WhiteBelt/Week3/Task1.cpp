// https://www.coursera.org/learn/c-plus-plus-white/programming/D5IKE/sortirovka-tsielykh-chisiel-po-moduliu
// Сортировка целых чисел по модулю
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, value;
    vector<int> array;

    cin >> n;

    for (auto i = 0; i < n; i++)
    {
        cin >> value;
        array.push_back(value);
    }

    sort(array.begin(), array.end(),
         [](const int &lhs, const int &rhs) { 
                if(abs(lhs) < abs(rhs))
                    return true;
                else
                    return false; });

    for (auto &i : array)
    {
        cout << i << ' ';
    }
    return 0;
}
