#include "action/move.hpp"

void Move::move(Element *elem, int dir) {
    dir &= MASK_DIRECTION;
    Position pos = elem->getPosition();
    int x = pos.getX();
    int y = pos.getY();
    switch (dir)
    {
    case UP:    elem->setPosition({x, y - 1});    break;
    case DOWN:  elem->setPosition({x, y + 1});    break;
    case LEFT:  elem->setPosition({x - 1, y});    break;
    case RIGHT: elem->setPosition({x + 1, y});    break;
    default: break;
    }
}