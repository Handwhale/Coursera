#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

// Плохое решение. ItRange не сработает от move iterator-а
// Много дублирования (move_iterator ctor)
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{

  // Если диапазон содержит меньше 2 элементов, выйти из функции.
  if (range_end - range_begin < 2)
    return;

  // Создать вектор, содержащий все элементы текущего диапазона.
  vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));

  // Разбить вектор на три равные части.
  size_t part_vector_size = elements.size() / 3;

  using ItRange = pair<RandomIt, RandomIt>;

  ItRange range1{elements.begin(), elements.begin() + part_vector_size};
  ItRange range2{range1.second, elements.end() - part_vector_size};
  ItRange range3{range2.second, elements.end()};

  // Вызвать функцию MergeSort от каждой части вектора.
  MergeSort(range1.first, range1.second);
  MergeSort(range2.first, range2.second);
  MergeSort(range3.first, range3.second);

  // Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter
  vector<typename RandomIt::value_type> tmp;
  merge(
      move_iterator(range1.first), move_iterator(range1.second),
      move_iterator(range2.first), move_iterator(range2.second),
      back_inserter(tmp));

  // Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2,
  // записав полученный отсортированный диапазон вместо исходного.
  merge(
      move_iterator(tmp.begin()), move_iterator(tmp.end()),
      move_iterator(range3.first), move_iterator(range3.second),
      range_begin);
}

void TestIntVector()
{
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

struct NoncopyableType
{
  int _data;

  bool operator==(const NoncopyableType &other) const
  {
    return _data == other._data;
  }

  bool operator<(const NoncopyableType &other) const
  {
    return _data < other._data;
  }

  NoncopyableType(const NoncopyableType &) = delete;
  NoncopyableType &operator=(const NoncopyableType &) = delete;

  NoncopyableType(NoncopyableType &&) = default;
  NoncopyableType &operator=(NoncopyableType &&) = default;
};

void TestNonCopyable()
{
  vector<NoncopyableType> data;
  data.push_back({1});
  data.push_back({2});
  data.push_back({3});
  data.push_back({4});
  data.push_back({5});

  MergeSort(begin(data), end(data));
  ASSERT(is_sorted(begin(data), end(data)));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestNonCopyable);
  return 0;
}
