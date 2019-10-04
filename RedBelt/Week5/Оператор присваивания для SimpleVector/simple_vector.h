#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector
{
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) : size(size), capacity(size), data(new T[size]) {}
    SimpleVector(const SimpleVector &other)
        : data(new T[other.capacity]),
          size(other.size),
          capacity(other.capacity)
    {
        copy(other.begin(), other.end(), begin());
    }
    ~SimpleVector() { delete[] data; }

    void operator=(const SimpleVector &rhs)
    {
        if (rhs.size <= capacity)
        {
            copy(rhs.begin(), rhs.end(), begin());
            size = rhs.size;
        }
        else
        {
            SimpleVector<T> tmp(rhs);
            swap(tmp.data, data);
            swap(tmp.size, size);
            swap(tmp.capacity, capacity);
        }
    }

    T &operator[](size_t index)
    {
        return data[index];
    }

    T *begin() { return data; }
    T *end() { return data + size; }

    const T *begin() const { return data; }
    const T *end() const { return data + size; }

    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }

    void PushBack(const T &value)
    {
        if (size == capacity)
        {
            IncreaseCapacity();
        }
        data[size] = value;
        ++size;
    }

private:
    T *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void IncreaseCapacity()
    {
        if (capacity == 0)
        {
            capacity = 1;
            data = new T[capacity];
        }
        capacity *= 2;
        T *new_data = new T[capacity];
        copy(data, &data[size], new_data);
        delete[] data;
        data = new_data;
    }
};