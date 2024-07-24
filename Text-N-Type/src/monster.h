#include <iostream>

#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
    std::string name;
    int health;
    float attack_chance = 0.5;
    float defense_boost = 0.05;
    bool is_defense = false;

public:
    void print_name();
    void print_health();
    int get_health();
    float get_attack_chance();
    void set_health();

    Monster()
    {
        this->health = 10;
        this->name = "Karen";
    }

    Monster(std::string name)
    {
        this->health = 10;
        this->name = name;
    }

    Monster(int health)
    {
        this->health = health;
        this->name = "Karen";
    }

    Monster(std::string name, int health)
    {
        this->health = health;
        this->name = name;
    }

    // Setters must be in the class itself if accessing private method
    void set_health(int health)
    {
        this->health = health;
    }
};

#endif