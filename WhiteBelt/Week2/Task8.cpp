// https://www.coursera.org/learn/c-plus-plus-white/programming/1mOPD/avtobusnyie-ostanovki-2
// Автобусные остановки — 2
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map<vector<string>, int> bus_stops_route_map;
    int command_count;
    int bus_stops_input;
    cin >> command_count;

    for (auto cc = 0; cc < command_count; cc++)
    {
        vector<string> temp_route;
        string bus_stop_name;
        cin >> bus_stops_input;

        for (auto i = 0; i < bus_stops_input; i++)
        {
            cin >> bus_stop_name;
            temp_route.push_back(bus_stop_name);
        }

        if (bus_stops_route_map.count(temp_route) == 0)
        {
            int route_number = bus_stops_route_map.size() + 1;
            bus_stops_route_map[temp_route] = route_number;
            cout << "New bus " << route_number << endl;
        }
        else
        {
            cout << "Already exists for " << bus_stops_route_map[temp_route] << endl;
        }
    }
}