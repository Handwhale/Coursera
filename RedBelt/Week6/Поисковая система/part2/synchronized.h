#pragma once
#include <shared_mutex>
using namespace std;

template <typename T>
class Synchronized
{
public:
  explicit Synchronized(T initial = T())
      : value(move(initial))
  {
  }

  struct ReadAccess
  {
    T &ref_to_value;
    shared_lock<shared_mutex> guard;
  };

  struct WriteAccess
  {
    T &ref_to_value;
    unique_lock<shared_mutex> guard;
  };

  ReadAccess GetReadAccess()
  {
    return {value, shared_lock(m)};
  }

  WriteAccess GetWriteAccess()
  {
    return {value, unique_lock(m)};
  }

private:
  T value;
  shared_mutex m;
};