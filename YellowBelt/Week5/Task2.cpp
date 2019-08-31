#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

//  базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
// классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
// функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.

// Гарантируется, что все команды ADD корректны; размеры всех фигур — это натуральные числа не больше 1000. В качестве значения π используйте 3,14.

class Figure
{
public:
    virtual string Name() = 0;
    virtual float Perimeter() = 0;
    virtual double Area() = 0;
};

class Triangle : public Figure
{
public:
    Triangle(int a, int b, int c) : _a(a), _b(b), _c(c) {}

    string Name() override
    {
        return "TRIANGLE";
    }

    float Perimeter() override
    {
        return _a + _b + _c;
    }

    double Area() override
    {
        double p = static_cast<double>(_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));
    }

private:
    double _a, _b, _c;
};

class Rect : public Figure
{
public:
    Rect(int width, int height) : _width(width), _height(height) {}

    string Name() override
    {
        return "RECT";
    }

    float Perimeter() override
    {
        return (_width + _height) * 2;
    }

    double Area() override
    {
        return _width * _height;
    }

private:
    int _width, _height;
};

class Circle : public Figure
{
public:
    Circle(int r) : _r(r) {}

    string Name() override
    {
        return "CIRCLE";
    }

    float Perimeter() override
    {
        return 2 * 3.14 * _r;
    }

    double Area() override
    {
        return 3.14 * _r * _r;
    }

private:
    int _r;
};

shared_ptr<Figure> CreateFigure(istringstream &is)
{

    string figure_name;
    is >> figure_name;

    if (figure_name == "TRIANGLE")
    {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    if (figure_name == "RECT")
    {
        int width, height;
        is >> width >> height;
        return make_shared<Rect>(width, height);
    }
    if (figure_name == "CIRCLE")
    {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }

    throw exception();
}

int main()
{
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto &current_figure : figures)
            {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}