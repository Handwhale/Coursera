// Чтение и вывод таблицы
// https://www.coursera.org/learn/c-plus-plus-white/programming/uyK0H/chtieniie-i-vyvod-tablitsy
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    const string file_path = "input.txt";
    ifstream input(file_path);
    int n, m;
    if (input)
    {
        input >> n;
        input.ignore(1);
        input >> m;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int temp;
                input >> temp;
                input.ignore(1);
                cout << setw(10);
                cout << temp;
            }
            if (n - 1 != i)
                cout << endl;
        }
    }
    return 0;
}
