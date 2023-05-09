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
    status &= MASK_DIRECTION;
    mStatus &= ~MASK_DIRECTION;
    mStatus |= status;
}
    
int** Element::getBitmap(int &rows, int &cols) {
    rows = mSize.getRows();
    cols = mSize.getCols();
    return pBitmap;
}
