#include "element/input.hpp"

Input::Input(int x, int y, int rows, int cols): Element(x, y, rows, cols)
{
}

Input::~Input()
{
}

void Input::input(int ch) {
    char c = ch;
    mInput += c;
}
