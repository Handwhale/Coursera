// Суммирование матриц
// https://www.coursera.org/learn/c-plus-plus-yellow/programming/CTQjw/summirovaniie-matrits
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix
{
public:
    Matrix()
    {
        _num_rows = 0;
        _num_cols = 0;
    }
    Matrix(int num_rows, int num_cols)
    {
        Reset(num_rows, num_cols);
    }
    void Reset(int num_rows, int num_cols)
    {
        if (num_rows < 0 || num_cols < 0)
        {
            throw out_of_range("Matrix couldn`t have negative size");
        }
        if (num_rows == 0 || num_cols == 0)
        {
            num_rows = num_cols = 0;
        }
        _matrix.assign(num_rows, vector<int>(num_cols));
        _num_rows = num_rows;
        _num_cols = num_cols;
    }

    int At(int num_rows, int num_cols) const
    {
        return _matrix.at(num_rows).at(num_cols);
    }

    int &At(int num_rows, int num_cols)
    {
        return _matrix.at(num_rows).at(num_cols);
    }

    int GetNumRows() const
    {
        return _num_rows;
    }

    int GetNumColumns() const
    {
        return _num_cols;
    }

private:
    vector<vector<int>> _matrix;
    int _num_rows, _num_cols;
};

istream &operator>>(istream &lhs, Matrix &rhs)
{
    int num_rows, num_cols, value;
    lhs >> num_rows >> num_cols;
    rhs = Matrix(num_rows, num_cols);
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            lhs >> value;
            rhs.At(i, j) = value;
        }
    }
    return lhs;
}

ostream &operator<<(ostream &lhs, const Matrix &rhs)
{
    lhs << rhs.GetNumRows() << ' ' << rhs.GetNumColumns() << endl;

    for (int i = 0; i < rhs.GetNumRows(); i++)
    {
        for (int j = 0; j < rhs.GetNumColumns(); j++)
        {
            lhs << rhs.At(i, j) << ' ';
        }
        lhs << endl;
    }
    return lhs;
}

bool operator==(const Matrix lhs, const Matrix rhs)
{
    if (lhs.GetNumRows() != rhs.GetNumRows() ||
        lhs.GetNumColumns() != rhs.GetNumColumns())
    {
        return false;
    }

    for (int i = 0; i < rhs.GetNumRows(); i++)
    {
        for (int j = 0; j < rhs.GetNumColumns(); j++)
        {
            if (lhs.At(i, j) != rhs.At(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.GetNumRows() != rhs.GetNumRows() ||
        lhs.GetNumColumns() != rhs.GetNumColumns())
    {
        throw invalid_argument("Matrices sizes have to be equal");
    }

    Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());

    for (int i = 0; i < rhs.GetNumRows(); i++)
    {
        for (int j = 0; j < rhs.GetNumColumns(); j++)
        {
            result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return result;
}

int main()
{
    Matrix one(0,1);
    Matrix two;

    cout << one + two;

    return 0;
}

// 3 5
// 6 4 -1 9 8
// 12 1 2 9 -5
// -4 0 12 8 6

// 3 5
// 5 1 0 -8 23
// 14 5 -6 6 9
// 8 0 5 4 1
