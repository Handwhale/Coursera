// Декомпозиция программы
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/k6Xm2/diekompozitsiia-proghrammy
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q)
{
    Query new_q;
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS")
    {
        new_q.type = QueryType::NewBus;

        string bus;
        is >> bus;
        new_q.bus = bus;

        int stops_count;
        is >> stops_count;

        for (int i = 0; i < stops_count; i++)
        {
            string value;
            is >> value;
            new_q.stops.push_back(value);
        }
    }
    else if (operation_code == "BUSES_FOR_STOP")
    {
        new_q.type = QueryType::BusesForStop;
        string stop;
        is >> stop;
        new_q.stop = stop;
    }
    else if (operation_code == "STOPS_FOR_BUS")
    {
        new_q.type = QueryType::StopsForBus;
        string bus;
        is >> bus;
        new_q.bus = bus;
    }
    else if (operation_code == "ALL_BUSES")
    {
        new_q.type = QueryType::AllBuses;
    }
    q = new_q;
    return is;
}

struct BusesForStopResponse
{
    vector<string> response_vect;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if (r.response_vect.size() == 0)
    {
        os << "No stop";
    }
    else
    {
        bool first = true;
        for (auto &item : r.response_vect)
        {
            if (!first)
            {
                os << ' ';
            }
            first = false;
            os << item;
        }
    }
    return os;
}

struct StopsForBusResponse
{
    string bus;
    vector<string> stops_vect;
    map<string, vector<string>> stops_to_busses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (r.stops_vect.size() == 0)
    {
        os << "No bus";
    }
    else
    {
        bool first = true;
        for (auto &stop : r.stops_vect)
        {
            if (!first)
            {
                os << endl;
            }
            first = false;
            os << "Stop " << stop << ": ";
            if (r.stops_to_busses.at(stop).size() == 1)
            {
                os << "no interchange";
            }
            else
            {
                for (auto &other_bus : r.stops_to_busses.at(stop))
                {
                    if (r.bus != other_bus)
                    {
                        os << other_bus << " ";
                    }
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse
{
    const map<string, vector<string>> &busses_to_stops_response;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if (r.busses_to_stops_response.empty())
    {
        os << "No buses";
    }
    else
    {
        for (auto &bus_item : r.busses_to_stops_response)
        {
            os << "Bus " << bus_item.first << ": ";
            for (auto &stop : bus_item.second)
            {
                os << stop << ' ';
            }
            os << endl;
        }
    }
    return os;
}

class BusManager
{
public:
    void AddBus(const string &bus, const vector<string> &stops)
    {
        buses_to_stops[bus] = stops;
        for (const auto &item : stops)
        {
            stops_to_buses[item].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const
    {
        if (stops_to_buses.count(stop) == 0)
        {
            return {}; // No stops
        }
        else
        {
            return {stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const
    {
        if (buses_to_stops.count(bus) == 0)
        {
            return {}; // No buses
        }
        else
        {
            return {bus, buses_to_stops.at(bus), stops_to_buses};
        }
    }

    AllBusesResponse GetAllBuses() const
    {
        return {buses_to_stops};
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main()
{
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        cin >> q;
        switch (q.type)
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}