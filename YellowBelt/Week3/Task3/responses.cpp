#include "responses.h"

#include <string>

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (r.response_vect.size() == 0) {
        os << "No stop";
    } else {
        bool first = true;
        for (auto &item : r.response_vect) {
            if (!first) {
                os << ' ';
            }
            first = false;
            os << item;
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (r.stops_vect.size() == 0) {
        os << "No bus";
    } else {
        bool first = true;
        for (auto &stop : r.stops_vect) {
            if (!first) {
                os << endl;
            }
            first = false;
            os << "Stop " << stop << ": ";
            if (r.stops_to_busses.at(stop).size() == 1) {
                os << "no interchange";
            } else {
                for (auto &other_bus : r.stops_to_busses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (r.busses_to_stops_response.empty()) {
        os << "No buses";
    } else {
        for (auto &bus_item : r.busses_to_stops_response) {
            os << "Bus " << bus_item.first << ": ";
            for (auto &stop : bus_item.second) {
                os << stop << ' ';
            }
            os << endl;
        }
    }
    return os;
}