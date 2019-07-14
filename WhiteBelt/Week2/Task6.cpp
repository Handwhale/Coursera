// https://www.coursera.org/learn/c-plus-plus-white/programming/gLemQ/iezhiemiesiachnyie-diela
// Ежемесячные дела
#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int> &v)
{
    int buffer = 0;
    for (auto i = 0; i < v.size() / 2; i++)
    {
        buffer = v[i];
        v[i] = v[v.size() - 1 - i];
        v[v.size() - 1 - i] = buffer;
    }
}

int DaysInMonth(int month)
{
    if (month % 12 == 2)
    {
        return 28;
    }
    if (month % 12 % 2 == 1)
    {
        return 31;
    }
    else
    {
        return 30;
    }
}

int main()
{
    int current_month = 1;
    vector<vector<string>> task_manager(31);
    int command_count;
    string operation;
    string task_name;
    int operation_value;

    cin >> command_count;
    for (auto i = 0; i < command_count; i++)
    {
        cin >> operation;
        if (operation == "ADD")
        {
            cin >> operation_value >> task_name;
            task_manager[operation_value - 1].push_back(task_name);
            continue;
        }
        if (operation == "NEXT")
        {
            int current_month_days = DaysInMonth(current_month);
            int next_month_days = DaysInMonth(current_month + 1);
            if (current_month_days < next_month_days)
            {
                task_manager.resize(next_month_days);
            }
            else
            {
                vector<string> delayed_tasks;
                for (auto i = next_month_days + 1; i <= current_month_days; i++)
                {
                    delayed_tasks.insert(delayed_tasks.end(), task_manager[i - 1].begin(), task_manager[i - 1].end());
                }
                task_manager.resize(next_month_days);
                task_manager.back().insert(task_manager.back().end(), delayed_tasks.begin(), delayed_tasks.end());
            }
            current_month++;
            continue;
        }
        if (operation == "DUMP")
        {
            cin >> operation_value;

            cout << task_manager[operation_value - 1].size() << ' ';
            for (auto i : task_manager[operation_value - 1])
            {
                cout << i << ' ';
            }
            cout << endl;

            continue;
        }
    }

    return 0;
}

// 12
// ADD 5 Salary
// ADD 31 Walk
// ADD 30 WalkPreparations
// NEXT
// DUMP 5
// DUMP 28
// NEXT
// DUMP 31
// DUMP 30
// DUMP 28
// ADD 28 Payment
// DUMP 28
