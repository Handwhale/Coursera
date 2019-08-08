// Строка
// https://www.coursera.org/learn/c-plus-plus-white/programming/zzTXi/stroka
#include <iostream>
#include <algorithm>

using namespace std;

class ReversibleString
{
public:
    ReversibleString() {}

    ReversibleString(string input_s)
    {
        s = input_s;
    }

    void Reverse()
    {
        reverse(s.begin(), s.end());
    }

    string ToString() const
    {
        return s;
    }

private:
    string s = "";
};

int main()
{
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;

    s.Reverse();
    const ReversibleString &s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;

    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}

// evil
// live
// ""