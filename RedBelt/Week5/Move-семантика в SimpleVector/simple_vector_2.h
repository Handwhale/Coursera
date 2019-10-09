#include <cstdint>
#include <algorithm>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector
{
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) : size(size), capacity(size), data(new T[size]) {}

    ~SimpleVector() { delete[] data; }

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
        data[size] = move(value);
        ++size;
    }

    void PushBack(T &&value)
    {
        if (size == capacity)
        {
            IncreaseCapacity();
        }
        data[size] = move(value);
        ++size;
    }

    // При необходимости перегрузите
    // существующие публичные методы

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
        auto new_data = new T[capacity];
        move(begin(), end(), new_data);
        delete[] data;
        data = new_data;
    }
};
