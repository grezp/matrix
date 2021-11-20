#pragma once
#include <vector>
#include "parse.h"

class Matrix
{
public:
    Matrix() {};
    Matrix(std::vector<std::vector<int>>mat, int mSize, int nSize)
        : data(mat), m_mSize(m_mSize), m_nSize(nSize) {};
    virtual ~Matrix() {};

    std::vector<std::vector<int>> data;

    bool ConvertFromStrings(const std::vector<std::vector<std::string>>& strings);
    void Print(const std::size_t &colWidth=10);
    Matrix Transpose();
    Matrix Multiply(const Matrix& data2);
    int GetMSize() const { return m_mSize; }
    int GetNSize() const { return m_nSize; }

private:
    int m_mSize;
    int m_nSize;
};

