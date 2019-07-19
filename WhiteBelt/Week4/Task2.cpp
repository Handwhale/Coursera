// Обратимая функцияОбратимая функция с умножением и делением
// https://www.coursera.org/learn/c-plus-plus-white/programming/oOkT1/obratimaia-funktsiia-s-umnozhieniiem-i-dielieniiem
// Возможно незачет из за приоритета опреаций умножения и деления над сложением и вычитанием
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FunctionPart
{
public:
    FunctionPart(char new_operation, double new_value)
    {
        operation = new_operation;
        value = new_value;
    }

    double Apply(double source_value) const
    {
        if (operation == '+')
        {
            return source_value + value;
        }
        if (operation == '-')
        {
            return source_value - value;
        }
        if (operation == '*')
        {
            return source_value * value;
        }
        else
        {
            return source_value / value;
        }
    }

    void Invert()
    {
        switch (operation)
        {
        case '+':
        {
            operation = '-';
            break;
        }

        case '-':
        {
            operation = '+';
            break;
        }
        case '*':
        {
            operation = '/';
            break;
        }
        case '/':
        {
            operation = '*';
            break;
        }

        default:
            break;
        }
    }

    // char GetOperation() const
    // {
    //     return operation;
    // }

private:
    char operation;
    double value;
};

class Function
{
public:
    void AddPart(char sign, double value)
    {
        // Если есть к чему приатачить * и /, значит надо аттачить, не создавая новую часть
        // при это Apply вроде как меняться не должен (применение в два этапа по приоритету не требуется)
        parts.push_back({sign, value});
    }
    double Apply(double value) const
    {
        // // operation priority
        // for (const auto &i : parts)
        // {
        //     auto part_op = i.GetOperation();
        //     if (part_op == '*' || part_op == '/')
        //         value = i.Apply(value);
        // }
        // for (const auto &i : parts)
        // {
        //     auto part_op = i.GetOperation();
        //     if (part_op == '+' || part_op == '-')
        //         value = i.Apply(value);
        // }

        for (const auto &part : parts)
        {
            value = part.Apply(value);
        }

        return value;
    }
    void Invert()
    {
        for (FunctionPart &part : parts)
        {
            part.Invert();
        }
        reverse(begin(parts), end(parts));
    }

private:
    vector<FunctionPart> parts;
};
