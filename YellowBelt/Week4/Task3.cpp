// Перебор перестановок
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/H4uPd/pieriebor-pieriestanovok
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void PrintVector(const vector<int> &vect)
{
    bool first = true;
    for (int item : vect)
    {
        if (first)
            first = false;
        else
            cout << ' ';

        cout << item;
    }
    cout << endl;
}

int main()
{
    int a;
    cin >> a;
    vector<int> permutation_vect;
    for (auto i = a; i > 0; i--)
    {
        permutation_vect.push_back(i);
    }

    do {
        PrintVector(permutation_vect);
    }
    while (prev_permutation(permutation_vect.begin(), permutation_vect.end()));
    

    return 0;
}