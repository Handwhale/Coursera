// Автобусные остановки — 3
// https://www.coursera.org/learn/c-plus-plus-white/programming/F7WBk/avtobusnyie-ostanovki-3
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main()
{
    map<set<string>, int> bus_stops_route_map;
    int command_count;
    int bus_stops_input;
    cin >> command_count;

    for (auto cc = 0; cc < command_count; cc++)
    {
        set<string> temp_route;
        string bus_stop_name;
        cin >> bus_stops_input;

        for (auto i = 0; i < bus_stops_input; i++)
        {
            cin >> bus_stop_name;
            temp_route.insert(bus_stop_name);
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
    return 0;
}