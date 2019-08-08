// Всё в квадрат
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/YQJs1/vsio-v-kvadrat
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

template <typename Key, typename Value>
Value &GetRefStrict(map<Key, Value> &dict, Key k)
{
    if (dict.count(k) != 1)
    {
        throw runtime_error("Key does not exist");
    }
    return dict.at(k);
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string &item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}