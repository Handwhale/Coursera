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
        bool is_current_lowp_op;
        if (sign == "*" || sign == "/")
            is_current_lowp_op = false;
        else
            is_current_lowp_op = true;

        if (is_last_lowp_op && !is_current_lowp_op)
            AddBrackets();

        is_last_lowp_op = is_current_lowp_op;

        result_deq.push_back(" " + sign + " " + to_string(value));
    }
    string GetResult()
    {
        ostringstream stream;
        for (const auto &item : result_deq)
        {
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
    bool is_last_lowp_op = false;
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