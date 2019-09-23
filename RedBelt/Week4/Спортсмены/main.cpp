#include <iostream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

list<int> row_of_athletes;
map<int, list<int>::const_iterator> number_to_iterator;

// O(LogN)
void InsertAthlet(const int &new_athlete_number, const int &next_athlete)
{
    auto map_it = number_to_iterator.find(next_athlete);

    if (map_it != number_to_iterator.end())
    {
        // if next_athlete is already exists
        auto list_it = row_of_athletes.insert(map_it->second, new_athlete_number);
        number_to_iterator[new_athlete_number] = list_it;
    }
    else
    {
        // if new athlete
        row_of_athletes.push_back(new_athlete_number);
        number_to_iterator[new_athlete_number] = prev(row_of_athletes.end());
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int athlete1, athlete2;
        cin >> athlete1 >> athlete2;
        InsertAthlet(athlete1, athlete2);
    }

    for (auto &i : row_of_athletes)
    {
        cout << i << ' ';
    }

    return 0;
}