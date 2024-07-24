#include <iostream>
#include "monster.h"

void Monster::print_name()
{
    std::cout << name << std::endl;
}

void Monster::print_health()
{
    std::cout << health << std::endl;
}

int Monster::get_health()
{
    return this->health;
}

float Monster::get_attack_chance()
{
    return this->attack_chance;
}