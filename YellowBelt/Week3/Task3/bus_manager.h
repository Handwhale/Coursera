#pragma once

#include "responses.h"
#include <vector>
#include <map>

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops);

    BusesForStopResponse GetBusesForStop(const string &stop) const;

    StopsForBusResponse GetStopsForBus(const string &bus) const;

    AllBusesResponse GetAllBuses() const;

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};
