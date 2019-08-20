// Имена и фамилии — 4
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/ye10B/imiena-i-familii-4
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        // добавить факт изменения имени на first_name в год year
        data.FirstNameHistory[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        // добавить факт изменения фамилии на last_name в год year
        data.LastNameHistory[year] = last_name;
    }
    string GetFullName(int year)
    {
        // получить имя и фамилию по состоянию на конец года year
        FindNearestYear(data.FirstNameHistory, year);
        auto fname_find_result = FindNearestYear(data.FirstNameHistory, year);
        auto lname_find_result = FindNearestYear(data.LastNameHistory, year);

        auto fnameIsEmpty = fname_find_result == "";
        auto lnameIsEmpty = lname_find_result == "";

        if (fnameIsEmpty && lnameIsEmpty)
        {
            return "Incognito";
        }

        if (fnameIsEmpty)
        {
            return lname_find_result + " with unknown first name";
        }

        if (lnameIsEmpty)
        {
            return fname_find_result + " with unknown last name";
        }
        return fname_find_result + " " + lname_find_result;
    }

private:
    struct PersonData
    {
        map<int, string> FirstNameHistory;
        map<int, string> LastNameHistory;
    };
    PersonData data;

    string FindNearestYear(map<int, string> &container, int &target_year)
    {
        auto it = container.upper_bound(target_year);

        if (it == container.begin())
            return "";
        else
            return prev(it)->second;
    }
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}

// Incognito
// Polina with unknown last name
// Polina Sergeeva
// Polina Sergeeva
// Appolinaria Sergeeva
// Polina Volkova
// Appolinaria Volkova