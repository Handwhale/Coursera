// https://www.coursera.org/learn/c-plus-plus-white/programming/c3YTB/otsortirovannyie-stroki
// Отсортированные строки
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class SortedStrings
{
public:
    void AddString(const string &s)
    {
        // добавить строку s в набор
        string_holder.push_back(s);
    }
    vector<string> GetSortedStrings()
    {
        // получить набор из всех добавленных строк в отсортированном порядке
        sort(string_holder.begin(), string_holder.end());
        return string_holder;
    }

private:
    // приватные поля
    vector<string> string_holder;
};

// void PrintSortedStrings(SortedStrings &strings)
// {
//     for (const string &s : strings.GetSortedStrings())
//     {
//         cout << s << " ";
//     }
//     cout << endl;
// }

// int main()
// {
//     SortedStrings strings;

//     strings.AddString("first");
//     strings.AddString("third");
//     strings.AddString("second");
//     PrintSortedStrings(strings);

//     strings.AddString("second");
//     PrintSortedStrings(strings);

//     return 0;
// }
