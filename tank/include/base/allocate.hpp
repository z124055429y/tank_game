#if !defined(_ALLOCATE_HPP_)
#define _ALLOCATE_HPP_

int** allocSpace(int rows, int cols);
void freeSpace(int **space, int rows, int cols);

#endif // _ALLOCATE_HPP_
