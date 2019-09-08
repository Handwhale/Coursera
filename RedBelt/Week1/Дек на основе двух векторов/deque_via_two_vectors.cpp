#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class Deque
{
public:
    Deque() {}
    bool Empty() const
    {
        return front_vector.empty() && back_vector.empty();
    }

    size_t Size() const
    {
        return front_vector.size() + back_vector.size();
    }

    T &operator[](const size_t &index)
    {
        auto res = get_correct_index(index);
        if (res.first)
        {
            return back_vector[res.second];
        }
        else
        {
            return front_vector[res.second];
        }
    }

    const T &operator[](const size_t &index) const
    {
        auto res = get_correct_index(index);
        if (res.first)
        {
            return back_vector[res.second];
        }
        else
        {
            return front_vector[res.second];
        }
    }

    T &At(const size_t &index)
    {
        auto res = get_correct_index(index);
        if (res.first)
        {
            return back_vector.at(res.second);
        }
        else
        {
            return front_vector.at(res.second);
        }
    }

    const T &At(const size_t &index) const
    {
        auto res = get_correct_index(index);
        if (res.first)
        {
            return back_vector.at(res.second);
        }
        else
        {
            return front_vector.at(res.second);
        }
    }

    T &Front()
    {
        return front_vector.empty() ? back_vector.front() : front_vector.back();
    }

    const T &Front() const
    {
        return front_vector.empty() ? back_vector.front() : front_vector.back();
    }

    T &Back()
    {
        return back_vector.empty() ? front_vector.front() : back_vector.back();
    }

    const T &Back() const
    {
        return back_vector.empty() ? front_vector.front() : back_vector.back();
    }

    void PushFront(const T &value)
    {
        front_vector.push_back(value);
    }

    void PushBack(const T &value)
    {
        back_vector.push_back(value);
    }

private:
    // false means front_vector
    pair<bool, size_t> get_correct_index(const size_t &index) const
    {
        auto fv_size = front_vector.size();

        if (index < fv_size)
        {
            // index in front vector
            return make_pair(false, fv_size - 1 - index);
        }
        else
        {
            // index in back vector
            return make_pair(true, index - fv_size);
        }
    }

    vector<T> front_vector, back_vector;
};