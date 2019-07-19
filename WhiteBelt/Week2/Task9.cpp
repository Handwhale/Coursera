// Синонимы
// https://www.coursera.org/learn/c-plus-plus-white/programming/WRbZE/sinonimy
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Synonim_map
{
public:
    void Add(string word1, string word2)
    {
        data[word1].insert(word2);
        data[word2].insert(word1);
    }
    size_t Count(string word)
    {
        return data[word].size();
    }
    string Check(string word1, string word2)
    {
        if (data[word1].count(word2) == 0)
        {
            return "NO";
        }
        else
        {
            return "YES";
        }
    }

private:
    map<string, set<string>> data;
};

int main()
{
    int n;
    string operation;
    cin >> n;
    Synonim_map s_map;

    for (int i = 0; i < n; i++)
    {
        cin >> operation;

        if (operation == "ADD")
        {
            string word1, word2;
            cin >> word1 >> word2;
            s_map.Add(word1, word2);
        }

        if (operation == "COUNT")
        {
            string word;
            cin >> word;
            cout << s_map.Count(word) << endl;
        }

        if (operation == "CHECK")
        {
            string word1, word2;
            cin >> word1 >> word2;
            cout << s_map.Check(word1, word2) << endl;
        }
    }

    return 0;
}

