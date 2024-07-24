#include <iostream>

#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{

    std::string name;
    int health;
    float attack_chance = 0.5;
    float defense_boost = 0.05;
    bool is_defense = false;

public:
    void print_name();
    void print_health();
    std::string get_name();
    int get_health();
    bool get_is_defense();
    float get_attack_chance();
    float get_defense_boost();
    void set_is_defense();
    void set_health();

    Character()
    {
        this->health = 10;
        this->name = "Karen";
    }

    Character(std::string name)
    {
        this->health = 10;
        this->name = name;
    }

    Character(int health)
    {
        this->health = health;
        this->name = "Karen";
    }

    Character(std::string name, int health)
    {
        this->health = health;
        this->name = name;
    }

    // Setters must be in the class itself if accessing private method
    // You can't have character:: before the method when in the class
    void set_is_defense(bool defense)
    {
        this->is_defense = defense;
    }

    void set_health(int health)
    {
        this->health = health;
    }
};

#endif