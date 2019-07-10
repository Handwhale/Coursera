// https://www.coursera.org/learn/c-plus-plus-white/programming/ZajnT/otbor-palindromov
// Отбор палиндромов
#include <iostream>
#include <vector>

using namespace std;

bool IsPalindrom(string word)
{
    for (auto i = 0; i < word.size() / 2; i++)
    {
        if (word[i] != word[word.size() - 1 - i])
        {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
    vector<string> result;
    for (auto i : words)
    {
        if ((i.size() >= minLength) && (IsPalindrom(i)))
        {
            result.push_back(i);
        }
    }
    return result;
}

int main()
{
    vector<string> words{"weew", "bro", "code"};

    for (auto i : PalindromFilter(words, 4))
    {
        cout << i << ", ";
    }
    cout << endl;
    return 0;
}
