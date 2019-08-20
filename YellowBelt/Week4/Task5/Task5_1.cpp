// Группировка по символу
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/AhGVS/gruppirovka-strok-po-priefiksu
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <map>
#include "/home/Handwhale/Документы/Coursera/YellowBelt/test_runner.h"

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix)
{

    RandomIt lower_bound_it = lower_bound(range_begin, range_end, prefix,
                                          [](const string &lhs, const char &rhs) {
                                              return lhs[0] < rhs;
                                          });

    RandomIt upper_bound_it = upper_bound(range_begin, range_end, prefix,
                                          [](const char &lhs, const string &rhs) {
                                              return lhs < rhs[0];
                                          });
    return make_pair(lower_bound_it, upper_bound_it);
}

void Tests()
{
    {
        vector<string> s;
        auto res = FindStartsWith(begin(s), end(s), 'm');
        auto expected = make_pair(begin(s), end(s));
        Assert(res == expected, "Empty vector");
    }
}

int main()
{
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}