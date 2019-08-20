// Разбиение на слова
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/PAhKJ/razbiieniie-na-slova
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "/home/Handwhale/Документы/Coursera/YellowBelt/test_runner.h"

// Проверь красивое решение

using namespace std;

vector<string> SplitIntoWords(const string &s)
{

    auto first_it = s.begin();
    auto last_it = s.begin();
    vector<string> result;

    bool first_loop = true;

    while (last_it != s.end())
    {
        if (!first_loop)
        {
            first_it = ++last_it;
        }
        else
        {
            first_loop = false;
        }
        last_it = find(last_it, s.end(), ' ');

        result.push_back(string(first_it, last_it));
    }
    return result;
}

void Tests()
{
    {
        string s = "C Cpp Java Python";
        vector<string> result = SplitIntoWords(s);
        vector<string> expected = {"C", "Cpp", "Java", "Python"};

        AssertEqual(result, expected, "Coursera test");
    }

    {
        string s = "";
        vector<string> result = SplitIntoWords(s);
        vector<string> expected = {};

        AssertEqual(result, expected, "Empty input");
    }

    {
        string s = "Cpp Java Python C";
        vector<string> result = SplitIntoWords(s);
        vector<string> expected = {"Cpp", "Java", "Python", "C"};

        AssertEqual(result, expected, "Last value with size = 1");
    }

    {
        string s = "C";
        vector<string> result = SplitIntoWords(s);
        vector<string> expected = {"C"};

        AssertEqual(result, expected, "One value");
    }
}

int main()
{
    Tests();
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it)
    {
        if (it != begin(words))
        {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
