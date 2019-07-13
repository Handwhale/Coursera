// https://www.coursera.org/learn/c-plus-plus-white/programming/8MK4d/razvorot-posliedovatiel-nosti
// Разворот последовательности
#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int> &v)
{
    int buffer = 0;
    for (auto i = 0; i < v.size() / 2; i++)
    {
        buffer = v[i];
        v[i] = v[v.size() - 1 - i];
        v[v.size() - 1 - i] = buffer;
    }
}

int main()
{
    vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);
    // numbers должен оказаться равен {2, 4, 3, 5, 1}
    return 0;
}
