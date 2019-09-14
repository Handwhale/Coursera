#include "profile.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Learner
{
private:
    set<string> dict;

public:
    int Learn(const vector<string> &words)
    {
        LOG_DURATION("Learn func");
        size_t start_size = dict.size();
        for (const auto &word : words)
        {
            dict.insert(word);
        }
        return dict.size() - start_size;
    }

    vector<string> KnownWords()
    {
        LOG_DURATION("KnownWords func");
        return {dict.begin(), dict.end()};
    }
};

std::string random_string(size_t length)
{
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

istringstream GetInput()
{
    string rstr;
    for (auto i = 0; i < 10000; i++)
    {
        rstr += random_string(10) + ' ';
    }

    return istringstream{rstr};
}

int main()
{

    auto cin = GetInput();
    Learner learner;
    string line;
    while (getline(cin, line))
    {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word)
        {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords())
    {
        // cout << word << "\n";
    }
}