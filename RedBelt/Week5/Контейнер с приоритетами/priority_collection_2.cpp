#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

template <typename T>
class PriorityCollection
{
public:
    // При переполнении size_t все неявно умрет
    using Id = size_t;
    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        Id unique_id = data.size();    
        auto it = priority.insert({0, unique_id}).first;
        data.push_back({move(object), it});
        return unique_id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin)
    {
        for (auto it = range_begin; it != range_end; it++)
        {
            *ids_begin = Add(move(*it));
            ++ids_begin;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        if (id + 1 > data.size())
            return false;

        return data[id].second != priority.end();
    }

    // Получить объект по идентификатору
    const T &Get(Id id) const
    {
        return data[id].first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        auto it = data[id].second;
        auto new_it = priority.insert({it->first + 1, it->second}).first;

        priority.erase(it);
        data[id].second = new_it;
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T &, int> GetMax() const
    {
        auto max_it = priority.rbegin();
        const T &element_ref = data[max_it->second].first;
        return {element_ref, max_it->first};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        pair<T, int> result;
        auto max_elem = priority.extract(prev(priority.end())).value();
        result.second = max_elem.first;
        result.first = move(data[max_elem.second].first);
        data[max_elem.second].second = priority.end();

        return result;
        // не удаляю из вектора, потому что это приведет к анигиляции решения
    }

private:
    set<pair<int, Id>> priority;
    vector<pair<T, set<pair<int, Id>>::iterator>> data;
};

class StringNonCopyable : public string
{
public:
    using string::string; // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;
    StringNonCopyable(StringNonCopyable &&) = default;
    StringNonCopyable &operator=(const StringNonCopyable &) = delete;
    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    strings.Get(yellow_id);
    {
        auto item2 = strings.GetMax();
        ASSERT_EQUAL(item2.first, "red");
        ASSERT_EQUAL(item2.second, 2);

        const auto item1 = strings.PopMax();
        ASSERT_EQUAL(item1.first, "red");
        ASSERT_EQUAL(item1.second, 2);
    }
    {
        auto item2 = strings.GetMax();
        ASSERT_EQUAL(item2.first, "yellow");
        ASSERT_EQUAL(item2.second, 2);

        const auto item1 = strings.PopMax();
        ASSERT_EQUAL(item1.first, "yellow");
        ASSERT_EQUAL(item1.second, 2);
    }
    {
        auto item2 = strings.GetMax();
        ASSERT_EQUAL(item2.first, "white");
        ASSERT_EQUAL(item2.second, 0);

        const auto item1 = strings.PopMax();
        ASSERT_EQUAL(item1.first, "white");
        ASSERT_EQUAL(item1.second, 0);
    }
    vector<StringNonCopyable> vct;
    vct.push_back("a");
    vct.push_back("b");
    vct.push_back("c");
    vector<size_t> ids(3);
    strings.Add(vct.begin(), vct.end(), ids.begin());
}

void TestAddWithIterators()
{
    PriorityCollection<string> strings;
    vector<string> data{"white", "yellow", "red"};
    vector<size_t> result;
    auto back_it = back_inserter(result);
    strings.Add(data.begin(), data.end(), back_it);

    auto exp = vector<size_t>{0,1,2};
    ASSERT_EQUAL(result, exp);

    for(auto i : result){
        strings.Promote(i);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestAddWithIterators);
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
