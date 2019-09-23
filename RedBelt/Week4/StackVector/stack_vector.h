#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector
{
public:
  explicit StackVector(size_t a_size = 0) : _size(a_size){
    if (N < a_size){
      throw invalid_argument("Vector size is larger than capacity");
    }
  }

  T &operator[](size_t index)
  {
    return _data[index];
  }
  const T &operator[](size_t index) const
  {
    return _data[index];
  }

  auto begin() { return _data.begin(); }
  auto end() { return _data.begin() + _size; }
  auto begin() const { return _data.begin(); }
  auto end() const { return _data.begin() + _size; }

  size_t Size() const
  {
    return _size;
  }
  size_t Capacity() const
  {
    return _data.size();
  }

  void PushBack(const T &value)
  {
    if (_size == N){
      throw overflow_error("Calling PushBack for full vector");
    }
    _data[_size] = value;
    _size++;
  }

  T PopBack()
  {
    if(_size == 0){
      throw underflow_error("Calling PopBack for empty vector");
    }
    _size--;
    return _data[_size];
  }

private:
  array<T, N> _data;
  size_t _size;
};
