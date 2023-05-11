#if !defined(_STATE_PAINTER_HPP_)
#define _STATE_PAINTER_HPP_

#include <cstdio>
#include <vector>

#include "base/allocate.hpp"
#include "element/state.hpp"

class StatePainter
{
public:
    void draw(State *state) {
        if (state == nullptr) return;
        int rows, cols;
        int **bitmap = state->getBitmap(rows, cols);
        
        fillSpace(bitmap, rows, cols, ' ');
        std::vector<int> scores = state->getScores();
        char *p = (char *)malloc(sizeof(char) * cols);
        for (int i = 0; i < scores.size(); ++i)
        {
            int n = 0;
            snprintf(p, cols, "Player score: %d%n", scores[i], &n);
            for (size_t j = 0; j < n; j++)
            {
                bitmap[i][j] = p[j];
            }
        }
        free(p);
    }
};

#endif // _STATE_PAINTER_HPP_
