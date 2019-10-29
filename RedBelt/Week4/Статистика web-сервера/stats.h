#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
using namespace std;

class Stats
{
public:
    Stats();

    void AddMethod(string_view method);

    void AddUri(string_view uri);
    
    const map<string_view, int> &GetMethodStats() const { return _method_stats; }
    const map<string_view, int> &GetUriStats() const { return _uri_stats; }

private:
    map<string_view, int> _method_stats;
    map<string_view, int> _uri_stats;
};

HttpRequest ParseRequest(string_view line);
Stats ServeRequests(istream& input);