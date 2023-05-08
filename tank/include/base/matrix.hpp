#if !defined(_MATRIX_HPP_)
#define _MATRIX_HPP_

#include <algorithm>

class Matrix
{
private:
    char **mData;
    int mRows;
    int mCols;
public:
    Matrix(int rows, int cols, char **data);
    ~Matrix();
    void rotate(int degree);
    void identity(int rows, int cols, char **data);
    char** allocSpace(int rows, int cols);
    void freeSpace(int rows, int cols, char **data);
};

Matrix::Matrix(int rows, int cols, char **data): mRows(rows + 1), mCols(cols + 1)
{
    mData = allocSpace(mRows, mCols);
}

Matrix::~Matrix()
{
    freeSpace(mRows, mCols, mData);
}
void Matrix::identity(int rows, int cols, char **data) {
}

char** Matrix::allocSpace(int rows, int cols) {
    char **data = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        mData[i] = new char[cols];
    }
    return data;
}

void Matrix::freeSpace(int rows, int cols, char **data) {
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::rotate(int degree) {
    char **rotate = allocSpace(mCols, mCols);
    
}

#endif // _MATRIX_HPP_
