#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include "test_runner.h"

using namespace std;

// Готовые ответы для методов Clients и Rooms
struct HotelStats
{
    int total_rooms_count = 0;
    map<int, int> total_clinets_count;
};

// Бронь
struct BookRecord
{
    long time;
    int client_id;
    int room_count;
};

struct HotelData
{
    HotelStats stats;
    queue<BookRecord> orders;
};

class BookingMachine
{
public:
    BookingMachine() {}

    void Book(const long &time, const string &hotel_name, const int &client_id, const int &room_count)
    {

        HotelData &hotel = hotel_to_data[hotel_name]; // Log N

        hotel.orders.push({time, client_id, room_count}); // Const
        hotel.stats.total_rooms_count += room_count;

        if (hotel.stats.total_clinets_count.count(client_id) == 0) // Log N
            hotel.stats.total_clinets_count[client_id] = 0;
        hotel.stats.total_clinets_count[client_id] += 1;

        long prev_time = actual_time;
        actual_time = time;
        if (time != prev_time)
            UpdateQueue();
    }

    int Clients(const string &hotel_name) const
    {
        try
        {
            return hotel_to_data.at(hotel_name).stats.total_clinets_count.size();
        }
        catch (exception &ex)
        {
            return 0;
        }
    }

    int Rooms(const string &hotel_name) const
    {
        try
        {
            return hotel_to_data.at(hotel_name).stats.total_rooms_count;
        }
        catch (exception &ex)
        {
            return 0;
        }
    }

private:
    static const int SECONDS_IN_DAY = 86400;
    map<string, HotelData> hotel_to_data;
    long actual_time;

    void UpdateQueue()
    {
        queue<string> empty_hotels;
        for (auto &hotel_data : hotel_to_data) // HotelSize
        {

            // Если информация превысила срок хранения

            while (actual_time - hotel_data.second.orders.front().time >= SECONDS_IN_DAY) // amortized Const
            {
                HotelStats &hotel_stats = hotel_data.second.stats;
                BookRecord &last_hotel_order = hotel_data.second.orders.front();

                hotel_stats.total_rooms_count -= last_hotel_order.room_count;

                if (hotel_stats.total_clinets_count[last_hotel_order.client_id] > 1)
                    hotel_stats.total_clinets_count[last_hotel_order.client_id]--;
                else
                {
                    hotel_stats.total_clinets_count.erase(last_hotel_order.client_id); // Log N

                    if (hotel_stats.total_clinets_count.size() == 0)
                    {
                        empty_hotels.push(hotel_data.first);
                    }
                }
                hotel_data.second.orders.pop();

                if (hotel_data.second.orders.size() == 0)
                    break;
            }
        }
        while (empty_hotels.size() != 0)
        {
            hotel_to_data.erase(empty_hotels.front());
            empty_hotels.pop();
        }
    }
};

void test()
{
    BookingMachine manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.Clients("mariott"), 0);
    ASSERT_EQUAL(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients("mariott"), 4);
    ASSERT_EQUAL(manager.Rooms("mariott"), 13);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 1);
    ASSERT_EQUAL(manager.Rooms("mariott"), 1);
    ASSERT_EQUAL(manager.Clients("hilton"), 1);
    ASSERT_EQUAL(manager.Rooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 2);
    ASSERT_EQUAL(manager.Rooms("mariott"), 2);
    ASSERT_EQUAL(manager.Clients("hilton"), 0);
    ASSERT_EQUAL(manager.Rooms("hilton"), 0);

    manager.Book(999999999999999000, "hilton", 3, 5);
    manager.Book(999999999999999900, "hilton", 4, 3);
    manager.Book(999999999999999990, "mariot", 6, 1);
    manager.Book(999999999999999999, "mariot", 6, 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 8);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("mariot"), 3);
    ASSERT_EQUAL(manager.Clients("mariot"), 1);
}

int main()
{
    TestRunner tr;
    tr.RunTest(test, "test");

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BookingMachine bm;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;

        if (query_type == "CLIENTS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << bm.Clients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS")
        {
            string hotel_name;
            cin >> hotel_name;
            cout << bm.Rooms(hotel_name) << endl;
        }
        else if (query_type == "BOOK")
        {
            long time;
            string hotel_name;
            int client_id;
            int room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            bm.Book(time, hotel_name, client_id, room_count);
        }
    }

    return 0;
}