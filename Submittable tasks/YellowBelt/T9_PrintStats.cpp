// Демографические показатели
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/iFaYj/diemoghrafichieskiie-pokazatieli
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Gender
{
    FEMALE,
    MALE
};

struct Person
{
    int age;          // возраст
    Gender gender;    // пол
    bool is_employed; // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end)
{
    if (range_begin == range_end)
    {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person &lhs, const Person &rhs) {
            return lhs.age < rhs.age;
        });
    return middle->age;
}

void PrintStats(vector<Person> persons)
{
    // supra bad 

    // All
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end())
         << endl;

    // Female
    auto fem_partition = partition(persons.begin(), persons.end(),
                                   [](const Person &person) { if (person.gender == Gender::FEMALE) return true;
                                                else return false; });
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), fem_partition) << endl;

    // Male
    auto male_partition = partition(persons.begin(), persons.end(),
                                   [](const Person &person) { if (person.gender == Gender::MALE) return true;
                                                else return false; });
    cout << "Median age for males = " << ComputeMedianAge(persons.begin(), male_partition) << endl;

    // Employed females
    auto emp_fem_partition = partition(persons.begin(), persons.end(),
                                   [](const Person &person) { if (person.gender == Gender::FEMALE && person.is_employed) return true;
                                                else return false; });
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), emp_fem_partition) << endl;

    // Unemployed females
    auto unemp_fem_partition = partition(persons.begin(), persons.end(),
                                   [](const Person &person) { if (person.gender == Gender::FEMALE && !person.is_employed) return true;
                                                else return false; });
    cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), unemp_fem_partition) << endl;

    // Employed males
    auto emp_male_partition = partition(persons.begin(), persons.end(),
                                   [](const Person &person) { if (person.gender == Gender::MALE && person.is_employed) return true;
                                                else return false; });
    cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), emp_male_partition) << endl;

    // Unemployed males
    auto unemp_male_partition = partition(persons.begin(), persons.end(),
                                   [](const Person &person) { if (person.gender == Gender::MALE && !person.is_employed) return true;
                                                else return false; });
    cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), unemp_male_partition) << endl;
}

// partition

int main()
{
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}