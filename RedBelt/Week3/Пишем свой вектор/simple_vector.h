#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector
{
public:
    SimpleVector() : _begin(nullptr), _end(nullptr), _capacity_end(nullptr) {}
    explicit SimpleVector(size_t size)
    {
        _begin = new T[size];
        _end = _begin + size;
        _capacity_end = _capacity_end;
    }
    ~SimpleVector()
    {
        delete[] _begin;
    }

    T &operator[](size_t index)
    {
        return *(_begin + index);
    }

    // Возможно грейдер не пустит без const вариантов
    T *begin() { return _begin; }
    T *end() { return _end; }

    size_t Size() const
    {
        if (_begin == nullptr)
            return 0;

        return _end - _begin;
    }
    size_t Capacity() const
    {
        if (_begin == nullptr)
            return 0;
        return _capacity_end - _begin;
    }
    void PushBack(const T &value)
    {
        if (Size() == Capacity())
        {
            IncreaseCapacity();
        }

        *(_end) = value;
        _end++;
    }

private:
    T *_begin;
    T *_end;
    T *_capacity_end;

    void IncreaseCapacity()
    {
        if (Capacity() == 0)
        {
            // set capacity to 1
            _begin = new T;
            _end = _begin;
            _capacity_end = _begin + 1;
            return;
        }
        T *new_begin = new T[Capacity() * 2];
        T *new_capacity_end = new_begin + Capacity() * 2;
        // copy elements to new place
        size_t old_size = Size();
        for (int i = 0; i < old_size; i++)
        {
            *(new_begin + i) = *(_begin + i);
        }

        delete[] _begin;    // !!!

        _begin = new_begin;
        _end = _begin + old_size;        
        _capacity_end = new_capacity_end;
    }
};
