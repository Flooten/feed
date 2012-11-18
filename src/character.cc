/*
 * FILNAMN:       character.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 * DATUM:         2012-11-15
 */

#include "character.h"

namespace feed
{
    Character::Character(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity,
                         SDL_Surface* image, int hitpoints, int armor)
                            : Object(position, size, velocity, image)
                            , hitpoints_(hitpoints)
                            , armor_(armor)
                            {}

    void Character::set_aim(glm::vec2 aim)
    {
        aim_ = aim;
    }

    glm::vec2 Character::get_aim() const
    {
        return aim_;
    }

    void Character::add_health(int value)
    {
        if (hitpoints_ + value < MAX_HEALTH)
        {
            hitpoints_ += value;
        }
        else
            hitpoints_ = MAX_HEALTH;
    }

    void Character::add_armor(int value)
    {
        if (armor_ + value < MAX_ARMOR)
        {
            armor_ += value;
        }
        else
            armor_ = MAX_ARMOR;
    }
}
