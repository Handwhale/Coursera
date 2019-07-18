// Второе вхождение
// https://www.coursera.org/learn/c-plus-plus-white/programming/SG7h0/vtoroie-vkhozhdieniie
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    int f_entry_count = 0;
    cin >> s;

    for (auto i = 0; i < s.size(); i++)
    {
        if (s[i] == 'f')
        {
            ++f_entry_count;
            if (f_entry_count == 2)
            {
                cout << i;
                break;
            }
        }
    }

    if (f_entry_count == 0)
    {
        cout << -2;
    }
    
    if(f_entry_count == 1)
    {
        cout << -1;
    }

    return 0;
}