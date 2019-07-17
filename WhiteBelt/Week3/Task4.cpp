// https://www.coursera.org/learn/c-plus-plus-white/programming/aN8U1/imiena-i-familii-2
// Имена и фамилии — 2
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
        auto first_name_year = FindNearestYear(data.FirstNameHistory, year);
        auto last_name_year = FindNearestYear(data.LastNameHistory, year);

        auto fnameIsEmpty = first_name_year == -1;
        auto lnameIsEmpty = last_name_year == -1;

        if (fnameIsEmpty && lnameIsEmpty)
        {
            return "Incognito";
        }

        if (fnameIsEmpty)
        {
            return data.LastNameHistory[last_name_year] + " with unknown first name";
        }

        if (lnameIsEmpty)
        {
            return data.FirstNameHistory[first_name_year] + " with unknown last name";
        }
        return data.FirstNameHistory[first_name_year] + " " + data.LastNameHistory[last_name_year];
    }

    string GetFullNameWithHistory(int year)
    {
        // получить все имена и фамилии по состоянию на конец года year
        string first_name_result, last_name_result;

        auto first_name_year = FindNearestYear(data.FirstNameHistory, year);
        auto last_name_year = FindNearestYear(data.LastNameHistory, year);

        auto fnameIsEmpty = first_name_year == -1;
        auto lnameIsEmpty = last_name_year == -1;

        if (fnameIsEmpty && lnameIsEmpty)
        {
            return "Incognito";
        }

        if (fnameIsEmpty)
        {
            return GetHistoryToThisYear(data.LastNameHistory, last_name_year) +
                   " with unknown first name";
        }

        if (lnameIsEmpty)
        {
            return GetHistoryToThisYear(data.FirstNameHistory, first_name_year) +
                   " with unknown last name";
        }
        return GetHistoryToThisYear(data.FirstNameHistory, first_name_year) +
               " " +
               GetHistoryToThisYear(data.LastNameHistory, last_name_year);
    }

private:
    struct PersonData
    {
        map<int, string> FirstNameHistory;
        map<int, string> LastNameHistory;
    };
    PersonData data;

    int FindNearestYear(map<int, string> &container, int &target_year)
    {
        int nearest_year = -1;
        for (auto &item : container)
        {
            if (item.first <= target_year)
            {
                nearest_year = item.first;
            }
            else
                break;
        }
        return container.count(nearest_year) != 0 ? nearest_year : -1;
    }

    string GetHistoryToThisYear(map<int, string> &container, int &target_year)
    {

        vector<string> histoty_vector;
        string prev_value = "";
        int nearest_year = -1;

        for (auto &item : container)
        {
            if (item.first <= target_year) // iterate from start to target year
            {
                if (item.second == prev_value) // exclude duplicate values
                {
                    continue;
                }
                else
                {
                    prev_value = item.second;
                    histoty_vector.push_back(item.second);
                }
            }
            else
                break;
        }

        if (histoty_vector.size() == 0)
            return "";

        if (histoty_vector.size() == 1)
            return histoty_vector.back();

        string result;
        string current_name = histoty_vector.back();
        histoty_vector.pop_back();

        for (auto it = histoty_vector.rbegin(); it != histoty_vector.rend(); it++)
        {
            result += *it + ", ";
        }

        result.erase(result.size() - 1 - 1, 2); // remove last ", "

        return current_name + " (" + result + ")";
    }
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
