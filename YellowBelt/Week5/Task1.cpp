#include <iostream>

using namespace std;

class Animal {
public:
    Animal(string param) : Name(param) {}

    const string Name;
};


class Dog : public Animal{
public:
    Dog(string param) : Animal(param) {

    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};
