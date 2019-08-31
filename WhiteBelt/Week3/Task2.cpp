// https://www.coursera.org/learn/c-plus-plus-white/programming/zqw0h/sortirovka-biez-uchiota-rieghistra
// Сортировка без учёта регистра
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string StringToLower(const string &str)
{
    string result;
    for (const auto &ch : str)
    {
        result += tolower(ch);
    }
    return result;
}

bool StringComparator(const string &lhs, const string &rhs)
{
    string low_lhs = StringToLower(lhs);
    string low_rhs = StringToLower(rhs);
    
    return low_lhs < low_rhs;
}

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

    sort(array.begin(), array.end(), StringComparator);

    for (const auto &i : array)
    {
        cout << i << ' ';
    }

    return 0;
}