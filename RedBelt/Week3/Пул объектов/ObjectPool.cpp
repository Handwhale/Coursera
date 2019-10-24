#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool
{
public:
    T *Allocate()
    {
        if (released_queue.empty())
        {
            return *(allocated_set.insert(new T).first);
        }
        return GetFromPool();
    }
    T *TryAllocate()
    {
        if (released_queue.empty())
        {
            return nullptr;
        }
        else
        {
            return GetFromPool();
        }
    }

    void Deallocate(T *object)
    {
        auto it_result = allocated_set.find(object);
        if (it_result == allocated_set.end())
        {
            throw invalid_argument("Object not found");
        }
        released_queue.push(*it_result);
        allocated_set.erase(it_result);
    }

    ~ObjectPool()
    {
        for (auto &i : allocated_set)
        {
            delete i;
        }

        while(!released_queue.empty())
        {
            delete released_queue.front();
            released_queue.pop();
        }
    }

private:
    set<T *> allocated_set;
    queue<T *> released_queue;

    T *GetFromPool()
    {
        auto released_obj = released_queue.front();
        released_queue.pop();
        return *(allocated_set.insert(released_obj).first);
    }
};

void TestObjectPool()
{
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
