// Построение арифметического выражения
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/SwfxR/postroieniie-arifmietichieskogho-vyrazhieniia
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <sstream>

using namespace std;

class ExpressionBuilder
{
public:
    ExpressionBuilder(int x)
    {
        result_deq.push_back(to_string(x));
    }
    void AddOperation(string sign, int value)
    {
        AddBrackets();
        result_deq.push_back(" " +sign + " " + to_string(value));
    }
    string GetResult(){
        ostringstream stream;
        for(const auto &item : result_deq){
            stream << item;
        }
        return stream.str();
    }

private:
    void AddBrackets()
    {
        result_deq.push_back(")");
        result_deq.push_front("(");
    }
    deque<string> result_deq;
};

int main()
{

    int x, n;

    cin >> x >> n;

    auto ex_builder = ExpressionBuilder(x);

    for (auto i = 0; i < n; i++)
    {
        string sign;
        int value;
        cin >> sign >> value;
        ex_builder.AddOperation(sign, value);
    }

    cout << ex_builder.GetResult();

    return 0;
}