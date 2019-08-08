// Масса блоков
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/pg1Vd/massa-blokov
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    // stringstream cin;
    // cin << "5 100" << endl;
    // for (int i = 0; i < 100000; i++)
    // {
    //     cin << "10000 10000 10000" << endl;
    // }

    int block_count; // количество блоков N не превосходит 10^5 int OK
    int density;     // плотность блоков R не превосходит 100 int OK
    int64_t total_weight = 0;

    cin >> block_count >> density;

    for (auto i = 0; i < block_count; i++)
    {
        int64_t w, h, d; // размеры блоков W, H, D не превосходят 10^4.
        cin >> w >> h >> d;
        total_weight += w * h * d * density;
    }

    cout << total_weight << endl;

    return 0;
}
