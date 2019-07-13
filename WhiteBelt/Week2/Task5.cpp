// https://www.coursera.org/learn/c-plus-plus-white/programming/XrhxI/ochieried
// Очередь
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int command_count;
    string operation;
    int value;
    vector<bool> queue;
    int total_worry_count;

    cin >> command_count;
    for (auto i = 0; i < command_count; i++)
    {
        cin >> operation;
        if (operation == "WORRY_COUNT")
        {
            cout << total_worry_count << endl;
            continue;
        }
        cin >> value;

        if (operation == "WORRY")
        {
            if (!queue[value])
            {
                queue[value] = true;
                total_worry_count++;
            }
            continue;
        }
        if (operation == "QUIET")
        {
            if (queue[value])
            {
                queue[value] = false;
                total_worry_count--;
            }
            continue;
        }
        if (operation == "COME")
        {
            if (value > 0)
            {
                queue.insert(queue.end(), value, false);
            }
            else
            {
                int worry_local_count = 0;
                for (auto i = queue.end() + value; i != queue.end(); i++)
                {
                    if (*i){
                        worry_local_count++;
                    }
                }
                total_worry_count-= worry_local_count;
                queue.erase(queue.end() + value, queue.end());
            }
            continue;
        }
    }

    return 0;
}

// 8
// COME 5
// WORRY 1
// WORRY 4
// COME -2
// WORRY_COUNT
// COME 3
// WORRY 3
// WORRY_COUNT

// ORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
// QUIET i: пометить i-го человека как успокоившегося;
// COME k: добавить k спокойных человек в конец очереди;
// COME -k: убрать k человек из конца очереди;
// WORRY_COUNT: узнать количество беспокоящихся людей в очереди.