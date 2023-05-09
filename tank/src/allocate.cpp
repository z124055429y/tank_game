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