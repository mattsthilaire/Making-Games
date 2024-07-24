#include <iostream>
#include "player.h"

bool Player::on_platform(Level *level)
{
    std::set<std::pair<int, int>>::iterator itr;

    for (itr = level->platform_pixels().begin(); itr != level->platform_pixels().end(); itr++)
    {

        // checks for player to be sitting atop a ledge. We have three ways this happens
        // 1.) Player is right on top of a platform
        // 2.) Player is haning off the left ledge of a platform
        // 3.) Player is hanging off the right ledge of a platform
        bool y_condition = this->y() + this->height() == itr->second;
        bool x_left_condition = this->x() + this->width() > itr->first && this->x() + this->width() <= itr->first + level->width();
        bool x_right_condition = this->x() > itr->first && this->x() <= itr->first + level->width();

        if (y_condition && (x_left_condition || x_right_condition))
        {
            return true;
        }
    }

    return false;
}

bool Player::hit_wall_left(Level *level)
{
    std::set<std::pair<int, int>>::iterator itr;

    for (itr = level->platform_pixels().begin(); itr != level->platform_pixels().end(); itr++)
    {

        // Conditions that stop player from moving through a wall going leftward
        // 1.) Player's left side is against a platform pixel
        // 2.) Player's pixel is above the platform pixel they are running into but will hit a platform pixel if they continue moving left
        // 3.) Player's pixel is below the platform pixel they are running into but will hit a platform pixel if they continue moving left
        bool x_condition = (this->x() - this->width()) == itr->first;
        bool y_condition_top = (this->y() > itr->second && this->y() < (itr->second + level->height()));
        bool y_condition_bottom = (this->y() + this->height() > itr->second && (this->y() + this->height()) < (itr->second + level->height()));

        if (x_condition && (y_condition_top || y_condition_bottom))
        {
            return true;
        }
    }

    return false;
}

bool Player::hit_wall_right(Level *level)
{
    std::set<std::pair<int, int>>::iterator itr;

    for (itr = level->platform_pixels().begin(); itr != level->platform_pixels().end(); itr++)
    {
        // Conditions that stop player from moving through a wall going leftward
        // 1.) Player's right side is against a platform pixel
        // 2.) Player's pixel is above the platform pixel they are running into but will hit a platform pixel if they continue moving right
        // 3.) Player's pixel is below the platform pixel they are running into but will hit a platform pixel if they continue moving right
        bool x_condition = (this->x() + this->width()) == itr->first;
        bool y_condition_top = (this->y() >= itr->second && this->y() <= (itr->second + level->height()));
        bool y_condition_bottom = (this->y() + this->height() > itr->second && (this->y() + this->height()) < (itr->second + level->height()));

        if (x_condition && (y_condition_top || y_condition_bottom))
        {
            return true;
        }
    }

    return false;
}

void Player::draw_player(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect pixel = {this->x(), this->y(), this->width(), this->height()};
    SDL_RenderFillRect(renderer, &pixel);
}