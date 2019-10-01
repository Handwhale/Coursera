#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <list>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
{
    size_t _size = last - first;
    vector<typename RandomIt::value_type> _correct_permutation;
    _correct_permutation.reserve(_size);

    list<size_t> index_list(_size);
    iota(index_list.begin(), index_list.end(), 0);
    auto list_it = index_list.begin(); // save iterator to avoid increase complexity
    list<size_t>::iterator it_to_remove;

    int i = 0;
    while (index_list.size() > 0)
    {
        for (; i < index_list.size();)
        {
            RandomIt elem_to_move = first + *list_it;
            _correct_permutation.push_back(move(*elem_to_move));
            it_to_remove = list_it;
            list_it = next(list_it, step_size);
            index_list.erase(it_to_remove);

            i += step_size - 1;
        }
        if (index_list.size() != 0)
        {
            i %= index_list.size();
            list_it = next(index_list.begin(), i);
        }
    }

    move(_correct_permutation.begin(), _correct_permutation.end(), first);
}

vector<int> MakeTestVector()
{
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector()
{
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt
{
    int value;

    //   NoncopyableInt(const NoncopyableInt&) = delete;
    //   NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    //   NoncopyableInt(NoncopyableInt&&) = default;
    //   NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
    return lhs.value == rhs.value;
}

ostream &operator<<(ostream &os, const NoncopyableInt &v)
{
    return os << v.value;
}

void TestAvoidsCopying()
{
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}
