#include "test_runner.h"
#include <vector>

using namespace std;

template <typename T>
class Table
{
public:
    Table(const size_t &row_count, const size_t &col_count)
        : _row_count(row_count), _col_count(col_count)
    {
        _table = vector<vector<T>>(row_count, vector<T>(col_count));
    }

    void Resize(size_t new_row_count, size_t new_col_count)
    {
        _table.resize(new_row_count);
        for (auto &row : _table)
        {
            row.resize(new_col_count);
        }
        _col_count = new_col_count;
        _row_count = new_row_count;
    }

    pair<size_t, size_t> Size() const
    {
        return {_row_count, _col_count};
    }

    vector<T> &operator[](const size_t &index)
    {
        auto x = _table[index];
        return _table[index];
    }

    const vector<T> &operator[](const size_t &index) const
    {
        return _table.at(index);
    }

private:
    size_t _row_count, _col_count;
    vector<vector<T>> _table;
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
