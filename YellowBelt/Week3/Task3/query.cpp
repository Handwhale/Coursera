#include "query.h"
#include <iostream>

istream &operator>>(istream &is, Query &q) {
    Query new_q;
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS") {
        new_q.type = QueryType::NewBus;

        string bus;
        is >> bus;
        new_q.bus = bus;

        int stops_count;
        is >> stops_count;

        for (int i = 0; i < stops_count; i++) {
            string value;
            is >> value;
            new_q.stops.push_back(value);
        }
    } else if (operation_code == "BUSES_FOR_STOP") {
        new_q.type = QueryType::BusesForStop;
        string stop;
        is >> stop;
        new_q.stop = stop;
    } else if (operation_code == "STOPS_FOR_BUS") {
        new_q.type = QueryType::StopsForBus;
        string bus;
        is >> bus;
        new_q.bus = bus;
    } else if (operation_code == "ALL_BUSES") {
        new_q.type = QueryType::AllBuses;
    }
    q = new_q;
    return is;
}
