#pragma once

#include "date.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


class Database {
public:
    // Add date event — добавить в базу данных пару (date, event)
    void Add(const Date &date, const std::string &event);

    // Print — вывести всё содержимое базы данных;
    void Print(std::ostream &os) const;

    // Del condition — удалить из базы все записи, которые удовлетворяют условию condition;
    template<class Lambda>
    int RemoveIf(const Lambda &predicate) {
        int delete_count = 0;
        std::vector<Date> dates_to_delete; // empty dates

        for (auto &pair : _data) {  // for every date
            for (auto event_it = pair.second.begin(); event_it != pair.second.end();) { // for every event
                if (predicate(pair.first, *event_it)) { // if pass condition
                    delete_count++;
                    if (_data[pair.first].size() == 1) { // if last element, delete date
                        // erasing later for simplicity
                        dates_to_delete.push_back(pair.first);
                        break;
                    }
                    // remove event from 2 containers otherwise
                    auto sorted_it = std::lower_bound(
                            _sorted_data[pair.first].begin(), _sorted_data[pair.first].end(), *event_it);
                    _sorted_data.at(pair.first).erase(sorted_it);
                    _data.at(pair.first).erase(event_it);
                } else
                    event_it++; // nothing changed (deleted), moving iterator forward
            }
        }

        for(auto &date : dates_to_delete){
            _data.erase(date);
            _sorted_data.erase(date);
        }

        return delete_count;
    }

    template<class Lambda>
    std::vector<std::pair<Date, std::string>> FindIf(const Lambda &predicate) const {
        std::vector<std::pair<Date, std::string>> result;
        for (auto &pair : _data)
            for (size_t i = 0; i < pair.second.size(); i++) {
                auto &event = pair.second[i];
                if (predicate(pair.first, event)) {
                    result.emplace_back(pair.first, event);
                }
            }
        return result;
    }

    // Last date — вывести запись с последним событием, случившимся не позже данной даты.
    std::pair<Date, std::string> Last(Date date) const;

private:
    std::map<Date, std::vector<std::string>> _data;
    // better than set, used for fast duplicate check
    std::map<Date, std::vector<std::string>> _sorted_data;
};

std::ostream &operator<<(std::ostream &os, const std::pair<Date, std::string> &db_pair);