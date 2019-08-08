// Множество значений словаря
// https://www.coursera.org/learn/c-plus-plus-white/programming/DULBh/mnozhiestvo-znachienii-slovaria
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string> &m)
{
    vector<string> string_value_vector;
    for(auto item : m){
            string_value_vector.push_back(item.second);
    }

    return set<string>(string_value_vector.begin(), string_value_vector.end());
}

int main()
{
    set<string> values = BuildMapValuesSet({{1, "odd"},
                                            {2, "even"},
                                            {3, "odd"},
                                            {4, "even"},
                                            {5, "odd"}});

    for (const string &value : values)
    {
        cout << value << endl;
    }

    return 0;
}