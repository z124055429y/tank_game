#include <cstring>

#include "base/allocate.hpp"

int** allocSpace(int rows, int cols) {
    int **space = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        space[i] = new int[cols];
    }
    return space;
}

void freeSpace(int **space, int rows, int cols) {
    for (int i = 0; i < rows; i++)
    {
        delete[] space[i];
    }
    delete[] space;
}

void clearSpace(int **space, int rows, int cols) {
    fillSpace(space, rows, cols, 0);
}

void fillSpace(int **space, int rows, int cols, int val) {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            space[i][j] = val;
        }
    }
}