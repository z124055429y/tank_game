#if !defined(_INPUT_PAINTER_CPP_)
#define _INPUT_PAINTER_CPP_

#include <cstdio>
#include <vector>

#include "base/allocate.hpp"
#include "element/input.hpp"

class InputPainter
{
public:
    void draw(Input *input) {
        if (input == nullptr) return;
        int rows, cols;
        int **bitmap = input->getBitmap(rows, cols);
        fillSpace(bitmap, rows, cols, ' ');
        std::string cmd = input->getInput();
        std::string tip = "Please input:";
        for (size_t i = 0; i < tip.size(); i++)
        {
            bitmap[0][i] = tip[i];
        }
        for (size_t i = 0; i < cmd.size(); i++)
        {
            bitmap[1][i] = cmd[i];
        }
    }
};

#endif // _INPUT_PAINTER_CPP_
