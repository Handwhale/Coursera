#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human(const string &new_name, const string &new_type) : _name(new_name), _type(new_type) {}
    virtual void Walk(const string &destination) const
    {
        cout << GetType() << ": " << _name << " walks to: " << destination << endl;
    }
    string GetName() const { return _name; }
    string GetType() const { return _type; }
    // Returns "Type: Name"
    string GetFullIdentification() const { return _type + ": " + _name; }

protected:
    string _name, _type;
};

class Student : public Human
{
public:
    Student(const string &name, const string &favouriteSong) : Human(name, "Student"), _favouriteSong(favouriteSong) {}

    void Learn() const
    {
        cout << GetFullIdentification() << " learns" << endl;
    }

    void Walk(const string &destination) const override
    {
        Human::Walk(destination);
        cout << GetFullIdentification() << " sings a song: " << _favouriteSong << endl;
    }

    void SingSong()
    {
        cout << GetFullIdentification() << " sings a song: " << _favouriteSong << endl;
    }

private:
    string _favouriteSong;
};

class Teacher : public Human
{
public:
    Teacher(const string &name, const string &subject) : Human(name, "Teacher"), _subject(subject) {}

    void Teach()
    {
        cout << "Teacher: " << _name << " teaches: " << _subject << endl;
    }

private:
    string _subject;
};

class Policeman : public Human
{
public:
    Policeman(const string &name) : Human(name, "Policeman") {}

    void Check(const Human &h)
    {
        cout << GetFullIdentification() << " checks " << h.GetType() << ". "
             << h.GetType() << "`s name is: " << h.GetName() << endl;
    }
};

void VisitPlaces(const Human &h, const vector<string> &places)
{
    for (const auto &p : places)
    {
        h.Walk(p);
    }
}

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
