#include <iostream>
#include <random>
#include "character.cc"
#include "monster.cc"

int main()
{

    // Ask user for name
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    // initalize character and monster
    Character character = Character(name, 1);
    Monster monster = Monster(10);

    std::cout << "GAME START!" << std::endl;

    // Create our random number generator and intialize input
    int input = 0;
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Game event loop. Determine that character and monster still have health left
    while (character.get_health() > 0 && monster.get_health() > 0)
    {

        // Player phase
        std::cout << "Pick Action: \n1.) Attack\n2.) Defend\n3.) End Game" << std::endl;
        std::cin >> input;

        // Router for player action choice
        switch (input)
        {
        case 1:
            std::cout << "1" << std::endl;
            if (distribution(gen) < character.get_attack_chance())
            {
                monster.set_health(monster.get_health() - 1);
                std::cout << "Success!" << std::endl;
            }
            else
            {
                std::cout << "Fail!" << std::endl;
            }
            break;
        case 2:
            std::cout << "2" << std::endl;
            character.set_is_defense(true);
            break;
        case 3:
            std::cout << "GAME EXITED" << std::endl;
            return -1; // exit out of game
        default:
            std::cout << "Please enter a valid action" << std::endl;
        }

        // Monster phase
        if (character.get_is_defense())
        {
            if (distribution(gen) < monster.get_attack_chance() - character.get_defense_boost())
            {
                character.set_health(character.get_health() - 1);
            }
        }
        else
        {
            if (distribution(gen) < monster.get_attack_chance())
            {
                character.set_health(character.get_health() - 1);
            }
        }

        std::cout << character.get_name() << " Health: " << character.get_health() << "\nMonster Health: " << monster.get_health() << std::endl;
    }

    if (character.get_health() > 0)
    {
        std::cout << "You WIN " << character.get_name() << std::endl;
    }
    else
    {
        std::cout << "The MONSTER has WON..." << std::endl;
    }

    return 0;
}