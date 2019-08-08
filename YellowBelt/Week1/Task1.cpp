// Средняя температура — 2
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/7T2kJ/sriedniaia-tiempieratura-2
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n; // не больше 6 000 000 (int ok)
    cin >> n;
    vector<int> temperatures(n);    // 100 000 000  ok
    int64_t sum = 0; // int не ок
    for (auto &temperature : temperatures)
    {
        cin >> temperature;
        sum += temperature;
    }

    int average = sum / n;
    vector<int> result_indices;
    for (auto i = 0; i < n; ++i)
    {
        if (temperatures[i] > average)
        {
            result_indices.push_back(i);
        }
    }

    cout << result_indices.size() << endl;
    for (int result_index : result_indices)
    {
        cout << result_index << " ";
    }
    cout << endl;

    return 0;
}