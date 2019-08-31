// Чтение и вывод таблицы
// https://www.coursera.org/learn/c-plus-plus-white/programming/uyK0H/chtieniie-i-vyvod-tablitsy
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

string RemoveLastSpaces(string str)
{
    int begin_offset = 0;
    int end_offset = 0;
    bool begin_sequence = true;
    bool end_sequence = true;
    for (int i = 0; i < str.size(); i++)
    {

        if (str[i] == ' ' && begin_sequence)
        {
            begin_offset++;
        }
        else
        {
            begin_sequence = false;
        }

        if (str[str.size() - i - 1] == ' ' && end_sequence)
        {
            end_offset++;
        }
        else
        {
            end_sequence = false;
        }

        if (!end_offset && !begin_offset)
            break;
    }

    auto new_begin = str.begin() + begin_offset;
    auto new_end = str.end() - end_offset;
    string result(new_begin, new_end);
    return result;
}

int main()
{
    const string file_path = "input.txt";
    ifstream input(file_path);

    int n, m;
    if (input)
    {
        input >> n >> m;

        int temp;
        input.ignore(256, '\n');

        for (int i = 0; i < n; i++)
        {
            bool is_first_element_in_row = true;
            for (int j = 0; j < m; j++)
            {
                if (m - 1 == j) // if last element in row
                {
                    input >> temp;
                    input.ignore(256, '\n');
                    // temp = RemoveLastSpaces(temp);
                }
                else
                {
                    input >> temp;
                    input.ignore(256, ','); // read value before \n
                }

                if (!is_first_element_in_row)
                    cout << ' ';
                else
                    is_first_element_in_row = false;
                cout << setw(10) << temp;
            }
            if (n - 1 != i) // if not last row
                cout << endl;
        }
    }
    return 0;
}