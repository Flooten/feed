/*
 * FILNAMN:       projectile.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "projectile.h"
#include "util.h"
#include "resources.h"
#include "character.h"
#include <iostream>             

namespace feed
{
    namespace
    {
        glm::vec2 getPistolOrigin(Character* shooter)
        {
            glm::vec2 origin;            

            if (shooter != nullptr)
            {
                if (shooter->getFacing() == 0)
                {
                    // Tittar åt höger
                    origin.x = shooter->get_position().x + 254;
                    origin.y = shooter->get_position().y + 210;
                }
                else
                {
                    // Tittar åt vänster
                    origin.x = shooter->get_position().x + 258;
                    origin.y = shooter->get_position().y + 210;
                }
            }

            return origin;
        }

        float getAimingAngle(Character* shooter)
        {
            glm::vec2 aim = shooter->get_aim();
            return atan(aim.y / aim.x);
        }
    }

    Projectile::Projectile(const glm::vec2& position,
                           const glm::vec2& size,
                           const glm::vec2& velocity,
                           SDL_Surface* image,
                           int damage)
        : Object(position, size, velocity, image)
        , damage_(damage)
    {
        setDirection(RIGHT);
    }

    int Projectile::get_damage() const
    {
        return damage_;
    }

    void Projectile::setDirection(Direction direction)
    {
        image_->setAnimation(direction);
    }

    Projectile* Projectile::createPistolProjectile(Object* sender)
    {
        // Sender är alltid åtminstone en Character
        Character* shooter = dynamic_cast<Character*>(sender);

        glm::vec2 position = getPistolOrigin(shooter);

        float angle = getAimingAngle(shooter);
        int radius = 198;

        position.x += radius * cos(angle);
        position.y += radius * sin(angle);

        glm::vec2 size(128, 128);
        glm::vec2 velocity = shooter->get_aim();
        velocity *= 100;

        // Beräkna allt ovan

        return new Projectile(position, size, velocity, Resources::instance().getImage("fireball"), 5);
    }
}
