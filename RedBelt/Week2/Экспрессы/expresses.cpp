#include "profile.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

class RouteManager
{
public:
    void AddRoute(int start, int finish)
    {
        // LOG_DURATION("AddRoute");
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const
    {
        // LOG_DURATION("FindNearestFinish");
        int result = abs(finish - start);

        if (reachable_lists_.count(start) == 0)
            return result;

        const set<int> &possible_expresses = reachable_lists_.at(start);
        if (possible_expresses.count(finish) > 0)
            // if direct path exists
            return 0;

        

        auto lb_it = possible_expresses.lower_bound(finish);
        if (lb_it != possible_expresses.end())
        {
            result = min(result,
                         abs(finish - *lb_it));
        }
        if (lb_it != possible_expresses.begin())
        {
            result = min(result,
                         abs(finish - *prev(lb_it)));
        }

        return result;
    }

private:
    map<int, set<int>> reachable_lists_;
};

int main()
{
    RouteManager routes;

    int query_count;
    cin >> query_count;
    LOG_DURATION("Total");

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD")
        {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO")
        {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
