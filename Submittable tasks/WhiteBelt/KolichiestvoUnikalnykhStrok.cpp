// Количество уникальных строк
// https://www.coursera.org/learn/c-plus-plus-white/programming/7rcDW/kolichiestvo-unikal-nykh-strok
#include <iostream>
#include <set>

using namespace std;

int main(){
    int n;
    set<string> unique_str;
    cin >> n;
    for(auto i = 0; i < n; i++)
    {
        string value;
        cin >> value;

        unique_str.insert(value);
    }

    cout << unique_str.size();

    return 0;
}