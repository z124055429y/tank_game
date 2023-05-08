#include <string.h>

#include "engine.hpp"
#include "handler.hpp"

int Handler::getcmd(char op) {
    int flag = 0;
    if (strchr("wasdc", op)) {
        flag |= PLAYER_ID_1;
    // } else if (strchr("ijkln", op)) {
    //     flag |= PLAYER_ID_2;
    } else {
        return 0;
    }
    switch (op)
    {
    case 'w': flag |= UP;       break;
    case 'a': flag |= LEFT;     break;
    case 's': flag |= DOWN;     break;
    case 'd': flag |= RIGHT;    break;
    default: break;
    }
    return flag;
}