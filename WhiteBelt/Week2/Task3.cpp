// https://www.coursera.org/learn/c-plus-plus-white/programming/nfWe8/pieriemieshchieniie-strok
// Перемещение строк
#include <iostream>
#include <vector>

using namespace std;

void MoveStrings(vector<string> &source, vector<string> &destination)
{
    for (auto i : source)
    {
        destination.push_back(i);
    }
    source.clear();
}

int main()
{
    vector<string> source = {"a", "b", "c"};
    vector<string> destination = {"z"};
    MoveStrings(source, destination);
    int i = 9;
    return 0;
}
