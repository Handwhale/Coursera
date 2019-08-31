// Масса блоков
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/pg1Vd/massa-blokov
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    int block_count;
    int density;     
    uint64_t total_weight = 0;

    cin >> block_count >> density;

    for (auto i = 0; i < block_count; i++)
    {
        uint64_t w, h, d; 
        cin >> w >> h >> d;
        total_weight += w * h * d * density;
    }

    cout << total_weight << endl;

    return 0;
}
