// Сортировка слиянием часть 2
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/wlbIg/sortirovka-sliianiiem
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    const int container_size = distance(range_begin, range_end);
    if (container_size < 2)     // 3?
        return;

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    int part_vector_size = container_size / 3;

    RandomIt elements_part1_begin = elements.begin();
    RandomIt elements_part2_begin = elements_part1_begin + part_vector_size;
    RandomIt elements_part3_begin = elements_part2_begin + part_vector_size;

    MergeSort(elements_part1_begin, elements_part2_begin);
    MergeSort(elements_part2_begin, elements_part3_begin);
    MergeSort(elements_part3_begin, elements.end());

    vector<typename RandomIt::value_type> temp_vect;
    merge(elements_part1_begin, elements_part2_begin, elements_part2_begin, elements_part3_begin, back_inserter(temp_vect));

    merge(temp_vect.begin(), temp_vect.end(), elements_part3_begin, elements.end(), range_begin);

}

int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
