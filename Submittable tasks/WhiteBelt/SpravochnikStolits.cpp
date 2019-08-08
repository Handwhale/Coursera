// https://www.coursera.org/learn/c-plus-plus-white/programming/ZUCo1/spravochnik-stolits
// Справочник столиц
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map<string, string> country_capital_map;
    int command_count;
    string operation;

    cin >> command_count;

    for (auto i = 0; i < command_count; i++)
    {
        cin >> operation;
        if (operation == "CHANGE_CAPITAL")
        {
            string country, new_capital;
            cin >> country >> new_capital;

            if (country_capital_map.count(country) == 0)
            {
                country_capital_map[country] = new_capital;
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
            }
            else
            {
                string old_capital = country_capital_map[country];
                if (old_capital == new_capital)
                {
                    cout << "Country " << country << " hasn't changed its capital" << endl;
                }
                else
                {
                    country_capital_map[country] = new_capital;
                    cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << endl;
                }
            }
            continue;
        }
        if (operation == "RENAME")
        {
            string old_country_name, new_country_name;
            cin >> old_country_name >> new_country_name;

            if (old_country_name == new_country_name ||
                country_capital_map.count(old_country_name) == 0 ||
                country_capital_map.count(new_country_name) != 0)
            {
                cout << "Incorrect rename, skip" << endl;
            }
            else
            {
                string capital_buffer = country_capital_map[old_country_name];
                country_capital_map[new_country_name] = capital_buffer;
                country_capital_map.erase(old_country_name);

                cout << "Country " << old_country_name << " with capital " << capital_buffer << " has been renamed to " << new_country_name << endl;
            }
            continue;
        }
        if (operation == "ABOUT")
        {
            string country;
            cin >> country;

            if (country_capital_map.count(country) != 0)
            {
                cout << "Country " << country << " has capital " << country_capital_map[country] << endl;
            }
            else
            {
                cout << "Country " << country << " doesn't exist" << endl;
            }
            continue;
        }
        if (operation == "DUMP")
        {
            if (country_capital_map.size() > 0)
            {
                for (auto item : country_capital_map)
                {
                    cout << item.first << '/' << item.second << ' ';
                }
                cout << endl;
            }
            else
            {
                cout << "There are no countries in the world" << endl;
            }
            continue;
        }
    }
    return 0;
}
