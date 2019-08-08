// Способы инициализации
// https://www.coursera.org/learn/c-plus-plus-white/programming/ZehLm/sposoby-initsializatsii

class Incognizable
{
public:
    Incognizable(){};
    Incognizable(int a){};
    Incognizable(int a, int b){};
};

int main()
{
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}