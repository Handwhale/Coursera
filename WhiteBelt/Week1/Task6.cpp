// Двоичные числа
// https://www.coursera.org/learn/c-plus-plus-white/programming/IbmX8/dvoichnyie-chisla
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    vector<int> binary_result;
    cin >> n;
    while (n != 0)
    {
        binary_result.push_back(n%2);
        n= n/2;
    }

    for(int i = binary_result.size() - 1; i >= 0; i--){
        cout << binary_result[i];
    }

    return 0;
}