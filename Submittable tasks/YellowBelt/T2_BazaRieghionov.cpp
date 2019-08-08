// База регионов
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/9CX0j/baza-rieghionov
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

enum class Lang
{
    DE,
    FR,
    IT
};

struct Region
{
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

bool operator<(const Region &lhs, const Region &rhs)
{
    auto lhs_tuple = tie(lhs.names, lhs.parent_std_name, lhs.population, lhs.std_name);
    auto rhs_tuple = tie(rhs.names, rhs.parent_std_name, rhs.population, rhs.std_name);
    return lhs_tuple < rhs_tuple;
}

int FindMaxRepetitionCount(const vector<Region> &regions)
{
    int result = 0;

    map<Region, int> region_counter;

    for (const auto &item : regions)
    {
        region_counter[item]++;
    }

    for (const auto &item : region_counter)
    {
        result = max(item.second, result);
    }
    
    return result;
}

int main()
{
    cout << FindMaxRepetitionCount({
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                 89},
                {"Russia",
                 "Eurasia",
                 {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                 89},
                {"Russia",
                 "Eurasia",
                 {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                 89},
            })
         << endl;

    cout << FindMaxRepetitionCount({
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                 89},
                {"Russia",
                 "Eurasia",
                 {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
                 89},
                {"Moscow",
                 "Toulouse",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                 31},
            })
         << endl;

    return 0;
}
