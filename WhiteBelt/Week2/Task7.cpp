// https://www.coursera.org/learn/c-plus-plus-white/programming/Gi9dw/avtobusnyie-ostanovki-1
// Автобусные остановки — 1
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

class BusTracker
{
public:
    // Добавить маршрут
    void NewBus(const string &bus_name, const vector<string> &stops)
    {
        for (const auto &bus_stop : stops)
        {
            bus_stops_map[bus_name].push_back(bus_stop);
            stop_buses_map[bus_stop].push_back(bus_name);
        }
    }

    // Вывести названия всех маршрутов автобуса, проходящих через остановку stop.
    void BusesForStop(const string &stop) const
    {
        if (stop_buses_map.count(stop) != 0)
        {
            for (const auto &item : stop_buses_map.at(stop))
            {
                cout << item << ' ';
            }
        }
        else
        {
            cout << "No stop";
        }
        cout << endl;
    }

    // Вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
    void StopsForBus(const string &bus) const
    {
        if (bus_stops_map.count(bus) != 0)
        {
            for (const auto &stop : bus_stops_map.at(bus))
            {
                cout << "Stop " << stop << ": ";

                if (stop_buses_map.at(stop).size() == 1)
                {
                    cout << "no interchange";
                }
                else
                {
                    for (const auto &bus_in_stop : stop_buses_map.at(stop))
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
    }

    // Вывести список всех маршрутов с остановками
    void AllBusses() const
    {
        if (bus_stops_map.size() != 0)
        {
            for (const auto &item : bus_stops_map)
            {
                cout << "Bus " << item.first << ":";
                for (const auto &stop : item.second)
                {
                    cout << ' ' << stop;
                }
                cout << endl;
            }
        }
        else
        {
            cout << "No buses" << endl;
        }
    }

private:
    map<string, vector<string>> bus_stops_map;
    map<string, vector<string>> stop_buses_map;
};

int main()
{
    int command_count;
    string operation;

    cin >> command_count;

    auto bt = BusTracker();

    for (auto i = 0; i < command_count; i++)
    {
        cin >> operation;
        if (operation == "NEW_BUS")
        {
            string bus;
            int stop_count;
            vector<string> stops;
            cin >> bus >> stop_count;

            for (auto i = 0; i < stop_count; i++)
            {
                string bus_stop;
                cin >> bus_stop;
                stops.push_back(bus_stop);
            }

            bt.NewBus(bus, stops);
            continue;
        }
        if (operation == "BUSES_FOR_STOP")
        {
            string stop;
            cin >> stop;

            bt.BusesForStop(stop);

            continue;
        }
        if (operation == "STOPS_FOR_BUS")
        {
            string bus;
            cin >> bus;

            bt.StopsForBus(bus);
            continue;
        }
        if (operation == "ALL_BUSES")
        {
            bt.AllBusses();
            continue;
        }
    }
    return 0;
}