#if !defined(_ALLOCATE_HPP_)
#define _ALLOCATE_HPP_

int** allocSpace(int rows, int cols);
void freeSpace(int **space, int rows, int cols);
void clearSpace(int **space, int rows, int cols);
void fillSpace(int **space, int rows, int cols, int val);

#endif // _ALLOCATE_HPP_
