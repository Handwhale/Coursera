#include "database.h"
#include <algorithm>

using namespace std;

void Database::Add(const Date &date, const std::string &event) {
    auto search_result = binary_search(_sorted_data[date].begin(), _sorted_data[date].end(), event);
    if (search_result) // duplicate
        return;
    auto it = lower_bound(_sorted_data[date].begin(), _sorted_data[date].end(), event);
    _sorted_data[date].insert(it, event);
    _data[date].push_back(event);
}

void Database::Print(std::ostream &os) const {
    for (const auto &pair : _data) {
        for (const auto &event : pair.second) {
            os << pair.first << ' ' << event << endl;
        }
    }
}

std::pair<Date, std::string> Database::Last(Date date) const {

    auto upp_bound_it = _data.upper_bound(date);    // map sorts its keys
    if (upp_bound_it == _data.begin())
        throw invalid_argument("Couldn't find events on this date");
    Date last_date = (--upp_bound_it)->first;
    string event = upp_bound_it->second.back();
    return {last_date, event};
}


std::ostream &operator<<(std::ostream &os, const std::pair<Date, std::string> &db_pair) {
    os << db_pair.first << ' ' << db_pair.second;
    return os;
}
