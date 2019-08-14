#include "bus_manager.h"
#include <vector>

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
    buses_to_stops[bus] = stops;
    for (const auto &item : stops) {
        stops_to_buses[item].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
    if (stops_to_buses.count(stop) == 0) {
        return {}; // No stops
    } else {
        return {stops_to_buses.at(stop)};
    }
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
    if (buses_to_stops.count(bus) == 0) {
        return {}; // No buses
    } else {
        return {bus, buses_to_stops.at(bus), stops_to_buses};
    }
}

AllBusesResponse BusManager::GetAllBuses() const {
    return {buses_to_stops};
}


