// Всё в квадрат
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/YQJs1/vsio-v-kvadrat
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

// Очень странное поведениие: коммент 17 и 18 строки ломает программу, но это не должно влиять на работу

// Предварительное объявление шаблонных функций

template <typename T>
T Sqr(T x);

template <typename Key, typename Value>
pair<Key, Value> Sqr(pair<Key, Value> x);

template <typename T>
vector<T> Sqr(vector<T> x);

template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> x);

// для обычных чисел
template <typename T>
T Sqr(T x)
{
    return x * x;
}

// для vector элементы нужно возвести в квадрат
template <typename T>
vector<T> Sqr(vector<T> x)
{
    for (auto &item : x)
    {
        item = Sqr(item);
    }
    return x;
}

// для map в квадрат нужно возвести только значения, но не ключи;
template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> x)
{

    for (auto &item : x)
    {
        item.second = Sqr(item.second);
    }
    return x;
}

// для pair в квадрат нужно возвести каждый элемент пары.
template <typename Key, typename Value>
pair<Key, Value> Sqr(pair<Key, Value> x)
{
    x.first = Sqr(x.first);
    x.second = Sqr(x.second);
    return x;
}

void MyTests()
{
    cout << "Numbers" << endl;
    vector<int> int_vect = {-2, 0, 2, 3};
    vector<float> float_vect = {-2, 0, 2, 3};

    for (auto &i : int_vect)
    {
        cout << Sqr(i) << ' ';
    }
    cout << endl;

    for (auto &i : float_vect)
    {
        cout << Sqr(i) << ' ';
    }
    cout << endl;

    cout << endl;
    cout << "Vectors" << endl;

    auto sqr_int_vect = Sqr(int_vect);
    for (auto &i : sqr_int_vect)
    {
        cout << i << ' ';
    }
    cout << endl;

    auto sqr_float_vect = Sqr(float_vect);
    for (auto &i : sqr_int_vect)
    {
        cout << i << ' ';
    }
    cout << endl;

    map<int, int> map_int = {{1, 1}, {2, 2}};
    map<int, int> sqr_map_int = Sqr(map_int);
    for (auto &i : sqr_map_int)
    {
        cout << i.first << ' ' << i.second;
        cout << endl;
    }
}

int main()
{
    // MyTests();
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}};
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs))
    {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}