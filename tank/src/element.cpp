#include "base/element.hpp"

Element::Element() : Element(0, 0, 0, 0) {}
Element::Element(int rows, int cols) : Element(0, 0, rows, cols) {}
Element::Element(int x, int y, int rows, int cols) : Element(x, y, rows, cols, NONE) {}
Element::Element(int x, int y, int rows, int cols, STATUS status): mPos(x, y), mSize(rows, cols), mStatus(status) {
    pBitmap = allocSpace(rows, cols);
}
Element::~Element() {
    freeSpace(pBitmap, mSize.getRows(), mSize.getCols());
}

Position Element::getPosition()
{
    return mPos;
}
void Element::setPosition(Position pos)
{
    mPos = pos;
}
Size Element::getSize()
{
    return mSize;
}
STATUS Element::getStatus()
{
    return mStatus;
}
void Element::setDirection(STATUS status)
{
    mStatus = status;
}
    
int** Element::getBitmap(int &rows, int &cols) {
    rows = mSize.getRows();
    cols = mSize.getCols();
    return pBitmap;
}

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