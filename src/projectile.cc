/*
 * FILNAMN:       projectile.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */

#include "projectile.h"
#include "util.h"
#include "resources.h"       

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
                    origin.x = shooter->get_position().x + 64;
                    origin.y = shooter->get_position().y + 53;
                }
                else
                {
                    // Tittar åt vänster
                    origin.x = shooter->get_position().x + 65;
                    origin.y = shooter->get_position().y + 53;
                }
            }

            return origin;
        }

        float getAimingAngle(Character* shooter)
        {
            glm::vec2 aim = shooter->get_aim();

            if (shooter->getFacing() == 0)
                aim.x = -aim.x;

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

    bool Projectile::get_boss_projectile() const
    {
        return boss_projectile_;
    }

    void Projectile::set_boss_projectile(bool val)
    {
        boss_projectile_ = val;
    }

    void Projectile::setDirection(Direction direction)
    {
        image_->setAnimation(direction);
    }

    Projectile* Projectile::createPistolProjectile(Character* shooter)
    {
        glm::vec2 position = getPistolOrigin(shooter);

        float angle = getAimingAngle(shooter);
        
        int radius = 0;
        float offset_angle = 0;

        if (angle < 0 * util::DEG_TO_RAD)
        {
            radius = 100;
            offset_angle = -10 * util::DEG_TO_RAD;
        }
        else
        {
            radius = 46;
            offset_angle = -40 * util::DEG_TO_RAD;
        }

        if (shooter->getFacing() == 0)
        {
            // Höger
            position.x += radius * cos(angle + offset_angle);
            position.y += radius * sin(-(angle + offset_angle));
        }
        else
        {
            // Vänster
            position.x -= radius * cos(angle + offset_angle);
            position.y -= radius * sin(angle + offset_angle);
        }
        
        glm::vec2 size(16, 16);
        glm::vec2 velocity = shooter->get_aim();
        velocity *= 500;

        return new Projectile(position, size, velocity, Resources::instance().getImage("fireball"), 5);
    }

    Projectile* Projectile::createShotgunProjectile(Character* shooter)
    {
        glm::vec2 position = getPistolOrigin(shooter);

        float angle = getAimingAngle(shooter);

        int radius;

        if (angle < -50 * util::DEG_TO_RAD)
            radius = 110;
        else
            radius = 52;

        float offset_angle = -10 * util::DEG_TO_RAD;

        if (shooter->getFacing() == 0)
        {
            // Höger
            position.x += radius * cos(angle + offset_angle);
            position.y += radius * sin(-(angle + offset_angle));
        }
        else
        {
            // Vänster
            position.x -= radius * cos(angle + offset_angle);
            position.y -= radius * sin(angle + offset_angle);
        }
        
        glm::vec2 size(16, 16);
        glm::vec2 velocity = util::randomizeVec2(shooter->get_aim(), 0.1f);
        velocity *= 300;

        return new Projectile(position, size, velocity, Resources::instance().getImage("fireball"), 5);
    }


}
