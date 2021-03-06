#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <vector>
#include <functional>
using namespace std;

template <typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin), last(end), size_(distance(first, last))
    {
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

    size_t size() const
    {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator
{
private:
    vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
    {
        for (size_t left = distance(begin, end); left > 0;)
        {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const
    {
        return pages.begin();
    }

    auto end() const
    {
        return pages.end();
    }

    size_t size() const
    {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C &c, size_t page_size)
{
    return Paginator(begin(c), end(c), page_size);
}

struct Stats
{
    map<string, int> word_frequences;

    void operator+=(const Stats &other)
    {
        for (auto &kv_pair : other.word_frequences)
        {
            word_frequences[kv_pair.first] += kv_pair.second;
        }
    }
};

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, IteratorRange<vector<string>::iterator> range)
{
    Stats result;
    string str;

    for (auto it = range.begin(); it != range.end(); it++)
    {
        if (key_words.count(*it) > 0)
        {
            result.word_frequences[*it] += 1;
        }
    }
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
    size_t future_count = 8;

    // Способ с нарезкой слов в вектор
    // выглядит медленно
    vector<string> str_data;
    string str_buf;
    // move??
    {
        LOG_DURATION("From stream to vector");
        while (input >> str_buf)
        {
            str_data.push_back(str_buf);
        }
    }

    // string str(input);
    // vector<string_view> str_data;

    size_t page_size = str_data.size() / future_count;

    vector<future<Stats>> futures;

    for (auto page : Paginate(str_data, page_size))
    {
        futures.push_back(
            async(
                ExploreKeyWordsSingleThread, ref(key_words), page));
    }

    Stats result;
    for (auto &item : futures)
    {
        result += item.get();
    }

    return result;
}

void TestBasic()
{

    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestSpeed()
{
    const int word_count = 10000000;
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
    string str = "";
    auto it = key_words.begin();
    for (int i = 0; i < word_count; i++)
    {
        str += "yangle ";
    }

    stringstream ss(str);
    {
        LOG_DURATION("Total speed test time");
        auto stats = ExploreKeyWords(key_words, ss);
        ASSERT_EQUAL(stats.word_frequences["yangle"], word_count);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    // RUN_TEST(tr, TestSpeed);
}
