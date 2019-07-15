// https://www.coursera.org/learn/c-plus-plus-white/programming/Gi9dw/avtobusnyie-ostanovki-1
// Автобусные остановки — 1
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map<string, vector<string>> bus_stops_map;
    map<string, vector<string>> stop_buses_map;
    int command_count;
    string operation;

    cin >> command_count;

    for (auto i = 0; i < command_count; i++)
    {
        cin >> operation;
        if (operation == "NEW_BUS")
        {
            string bus;
            int stop_count;
            cin >> bus >> stop_count;
            for (auto i = 0; i < stop_count; i++)
            {
                string bus_stop;
                cin >> bus_stop;
                bus_stops_map[bus].push_back(bus_stop);
                stop_buses_map[bus_stop].push_back(bus);
            }
            continue;
        }
        if (operation == "BUSES_FOR_STOP")
        {
            string stop;
            cin >> stop;

            if (stop_buses_map[stop].size() != 0)
            {
                for (const auto &item : stop_buses_map[stop])
                {
                    cout << item << ' ';
                }
            }
            else
            {
                cout << "No stop";
            }
            cout << endl;
            continue;
        }
        if (operation == "STOPS_FOR_BUS")
        {
            string bus;
            cin >> bus;

            if (bus_stops_map[bus].size() != 0)
            {
                for (const auto &stop : bus_stops_map[bus])
                {
                    cout << "Stop " << stop << ": ";

                    if (stop_buses_map[stop].size() == 1)
                    {
                        cout << "no interchange";
                    }
                    else
                    {
                        for (const auto &bus_in_stop : stop_buses_map[stop])
                        {
                            if (bus_in_stop != bus)
                            {
                                cout << bus_in_stop << ' ';
                            }
                        }
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "No bus" << endl;
            }
            continue;
        }
        if (operation == "ALL_BUSES")
        {
            if (bus_stops_map.size() != 0)
            {
                for (const auto &item : bus_stops_map)
                {
                    cout << "Bus " << item.first << ": ";
                    for (const auto &stop : item.second)
                    {
                        cout << stop << ' ';
                    }
                    cout << endl;
                }
            }
            else
            {
                cout << "No buses" << endl;
            }
            continue;
        }
    }
    return 0;
}
