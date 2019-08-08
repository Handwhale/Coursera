// Трекер задач
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/f9Art/triekier-zadach
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

enum class TaskStatus
{
    NEW,         
    IN_PROGRESS, 
    TESTING,     
    DONE         
};

TaskStatus Next(const TaskStatus &ts)
{
    return TaskStatus(static_cast<int>(ts) + 1);
}


using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
    const TasksInfo &GetPersonTasksInfo(const string &person) const
    {
        return _person_to_task.at(person);
    }

    void AddNewTask(const string &person)
    {
        _person_to_task[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string &person, int task_count)
    {
        if (_person_to_task.count(person) == 0)
            return {{}, {}};
        TasksInfo new_task_info = _person_to_task.at(person);
        TasksInfo &old_task_info = _person_to_task.at(person);

        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;

        for (const auto &item : old_task_info)
        {
            int task_changed = 0;
            if (task_count > 0)
            {

                if (item.second <= task_count)
                {
                    task_count -= item.second;
                    task_changed = item.second;
                }
                else
                {
                    task_changed = task_count;
                    task_count = 0;
                }
                if (item.first != TaskStatus::DONE)
                {
                    new_task_info[item.first] -= task_changed;

                    if (task_changed != 0)
                    {
                        new_task_info[Next(item.first)] += task_changed;
                        updated_tasks[Next(item.first)] += task_changed;
                    }
                }
            }

            int current_untouched_task = old_task_info[item.first] - task_changed;

            if (item.first != TaskStatus::DONE && current_untouched_task != 0)
            {
                untouched_tasks[item.first] = current_untouched_task;
            }
        }
        old_task_info = new_task_info;
        return tie(updated_tasks, untouched_tasks);
    }

private:
    map<string, TasksInfo> _person_to_task;
};

string NumberToStatus(int i)
{
    switch (i)
    {
    case 0:
        return "NEW";
        break;

    case 1:
        return "IN_PROGRESS";
        break;

    case 2:
        return "TESTING";
        break;

    case 3:
        return "DONE";
        break;

    default:
        return "ERROR";
        break;
    }
}

void PrintTasksInfo(const TasksInfo &tasks_info)
{
    cout << " { ";
    for (int i = 0; i < 4; i++)
    {
        if (tasks_info.count(TaskStatus(i)) != 0)
        {
            cout << NumberToStatus(i) << " : " << tasks_info.at(TaskStatus(i)) << ", ";
        }
    }
    cout << "}   ";
}

void PerformTaskWrapper(tuple<TasksInfo, TasksInfo> tup)
{
    get<0>(tup);
    cout << "Updated: ";
    PrintTasksInfo(get<0>(tup));
    cout << "Untouched: ";
    PrintTasksInfo(get<1>(tup));
    cout << endl;
}

int main()
{
    TeamTasks tasks;

    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }

    PerformTaskWrapper(tasks.PerformPersonTasks("Alice", 5));
    PerformTaskWrapper(tasks.PerformPersonTasks("Alice", 5));
    PerformTaskWrapper(tasks.PerformPersonTasks("Alice", 1));
    cout << endl
         << endl
         << endl;

    auto qweqwe = tasks.PerformPersonTasks("Alice", 0);

    // AddNewTasks Alice 5
    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }

    // PerformPersonTasks Alice 2
    PerformTaskWrapper(tasks.PerformPersonTasks("Alice", 2));
    // GetPersonTasksInfo Alice
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl;

    // PerformPersonTasks Alice 4
    PerformTaskWrapper(tasks.PerformPersonTasks("Alice", 4));

    //GetPersonTasksInfo Alice
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl;

    return 0;
}
