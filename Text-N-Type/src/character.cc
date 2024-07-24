#include <iostream>
#include "character.h"

void Character::print_name()
{
    std::cout << name << std::endl;
}

void Character::print_health()
{
    std::cout << health << std::endl;
}

std::string Character::get_name()
{
    return this->name;
}

int Character::get_health()
{
    return this->health;
}

bool Character::get_is_defense()
{
    return this->is_defense;
}

float Character::get_attack_chance()
{
    return this->attack_chance;
}

float Character::get_defense_boost()
{
    return this->defense_boost;
}