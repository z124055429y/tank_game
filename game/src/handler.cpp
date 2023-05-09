#include <string.h>

#include "engine.hpp"
#include "handler.hpp"

int Handler::generateCommand(char op) {
    int flag = 0;
    if (strchr("wasdc", op)) {
        flag |= PLAYER_ID_1;
    } else if (strchr("ijkln", op)) {
        flag |= PLAYER_ID_2;
    } else {
        return 0;
    }
    switch (op)
    {
        case 'w': case 'i': flag |= UP;       break;
        case 'a': case 'j': flag |= LEFT;     break;
        case 's': case 'k': flag |= DOWN;     break;
        case 'd': case 'l': flag |= RIGHT;    break;
        case 'c': case 'n': flag |= FIRE;     break;
        default: break;
    }
    return flag;
}