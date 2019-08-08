// Вывод с точностью
// https://www.coursera.org/learn/c-plus-plus-white/programming/ndSVY/vyvod-s-tochnost-iu
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    const string file_path = "input.txt";
    ifstream input(file_path);
    string line;

    cout << fixed << setprecision(3);

    if (input)
    {
        while (getline(input, line))
        {
            cout << stod(line) << endl;
        }
    }
    return 0;
}