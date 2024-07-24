#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int x, y;

public:
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);

    Player()
    {
        this->x = 0;
        this->y = 0;
    }

    Player(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif