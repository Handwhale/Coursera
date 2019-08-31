// Часть множества
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/LSMnD/chast-mnozhiestva

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border)
{

  auto upper_bound_it = upper_bound(elements.begin(), elements.end(), border);

  vector<T> result(upper_bound_it, elements.end());
  return result;
}

int main()
{
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 6))
  {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}