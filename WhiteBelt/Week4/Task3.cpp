// Работа с файлами
// https://www.coursera.org/learn/c-plus-plus-white/programming/NZTXy/rabota-s-failami
// ЗАДАЧА В 2 ЧАСТИ, ПЕРЕТАЩИ ЧАСТИ В MAIN
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Part1()
{
    const string file_path = "input.txt";
    ifstream input(file_path);
    string line;
    if (input)
    {
        while (getline(input, line))
        {
            cout << line << endl;
        }
    }
}

void Part2()
{
    const string output_file_path = "output.txt";
    const string input_file_path = "input.txt";
    ofstream output(output_file_path);
    ifstream input(input_file_path);

    string line;

    if (input)
    {
        while (getline(input, line))
        {
            output << line << endl;
        }
    }
}

int main()
{
    Part2();
    return 0;
}
