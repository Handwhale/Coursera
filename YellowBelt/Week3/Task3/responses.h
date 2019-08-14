#pragma once

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse {
    vector<string> response_vect;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse {
    string bus;
    vector<string> stops_vect;
    map<string, vector<string>> stops_to_busses;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse {
    const map<string, vector<string>> &busses_to_stops_response;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);