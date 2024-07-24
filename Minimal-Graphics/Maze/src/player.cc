#include <iostream>
#include "player.h"

int Player::get_x()
{
    return this->x;
}

int Player::get_y()
{
    return this->y;
}

void Player::set_x(int offset)
{
    this->x += offset;
}

void Player::set_y(int offset)
{
    this->y += offset;
}