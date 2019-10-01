#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
using namespace std;

class Stats
{
public:
    Stats()
    {
        _method_stats = {
            {"GET", 0},
            {"PUT", 0},
            {"POST", 0},
            {"DELETE", 0},
            {"UNKNOWN", 0},
        };
        _uri_stats = {
            {"/", 0},
            {"/order", 0},
            {"/product", 0},
            {"/basket", 0},
            {"/help", 0},
            {"unknown", 0},
        };
    }
    void AddMethod(string_view method)
    {
        if (_method_stats.find(method) != _method_stats.end())
        {
            ++_method_stats[method];
        }
        else
        {
            ++_method_stats["UNKNOWN"];
        }
    }
    void AddUri(string_view uri)
    {
        if (_uri_stats.find(uri) != _uri_stats.end())
        {
            ++_uri_stats[uri];
        }
        else
        {
            ++_uri_stats["unknown"];
        }
    }
    const map<string_view, int> &GetMethodStats() const { return _method_stats; }
    const map<string_view, int> &GetUriStats() const { return _uri_stats; }

private:
    map<string_view, int> _method_stats;
    map<string_view, int> _uri_stats;
};

HttpRequest ParseRequest(string_view line)
{
    vector<string_view> str_args;
    str_args.reserve(3);
    size_t pos = line.find_first_not_of(' ');
    while (true)
    {
        size_t space = line.find(' ', pos);

        if (space == line.npos)
        {
            str_args.push_back(line.substr(pos));
            break;
        }
        else
        {
            str_args.push_back(line.substr(pos, space - pos));
            pos = space + 1;
        }
    }

    return {str_args[0], str_args[1], str_args[2]};
}
