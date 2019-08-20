// Сортировка слиянием часть 1
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/wlbIg/sortirovka-sliianiiem
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

// Проверь правильное решение

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    const int container_size = distance(range_begin, range_end);
    if (container_size < 2)
        return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    RandomIt elements_begin = elements.begin();
    RandomIt elements_end = elements.end();

    RandomIt elements_middle_it = elements_begin + container_size / 2;

    MergeSort(elements_begin, elements_middle_it);
    MergeSort(elements_middle_it, elements_end);

    merge(elements_begin, elements_middle_it, elements_middle_it, elements_end, range_begin);
}

int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
