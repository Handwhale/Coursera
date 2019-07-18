// https://www.coursera.org/learn/c-plus-plus-white/programming/6rEoc/imiena-i-familii-3
// Имена и фамилии — 3
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Person
{
public:
    Person(string first_name, string last_name, int year)
    {
        data.FirstNameHistory[year] = first_name;
        data.LastNameHistory[year] = last_name;
    }

    void ChangeFirstName(int year, const string &first_name)
    {
        if (data.LastNameHistory.begin()->first > year)
            return;
        data.FirstNameHistory[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        if (data.LastNameHistory.begin()->first > year)
            return;
        data.LastNameHistory[year] = last_name;
    }
    string GetFullName(int year)
    {
        if (data.FirstNameHistory.begin()->first > year)
            return "No person";
        // получить имя и фамилию по состоянию на конец года year
        auto first_name_year = FindNearestYear(data.FirstNameHistory, year);
        auto last_name_year = FindNearestYear(data.LastNameHistory, year);

        return data.FirstNameHistory[first_name_year] + " " + data.LastNameHistory[last_name_year];
    }

    string GetFullNameWithHistory(int year)
    {
        if (data.FirstNameHistory.begin()->first > year)
            return "No person";
        // получить все имена и фамилии по состоянию на конец года year
        string first_name_result, last_name_result;

        auto first_name_year = FindNearestYear(data.FirstNameHistory, year);
        auto last_name_year = FindNearestYear(data.LastNameHistory, year);

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
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
