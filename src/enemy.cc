/*
 * FILNAMN:       enemy.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-26
 *
 */

#include "enemy.h"
#include "resources.h"

namespace feed
{
    Enemy::Enemy(const glm::vec2& position,
                 const glm::vec2& size,
                 const glm::vec2& velocity,
                 SDL_Surface* image,
                 int hitpoints,
                 int armor,
                 int max_health,
                 int max_armor,
                 int weapon_type)
        : Character(position, size, velocity, image, hitpoints, armor, max_health, max_armor)
        , weapon_(nullptr)
    {
        switch (weapon_type)
        {
            case SMG:
                weapon_ = nullptr;
                break;

            default:
                break;
        }
    }

    Enemy::~Enemy()
    {
        delete weapon_;
    }

    void Enemy::fire()
    {
        if (weapon_ != nullptr)
            weapon_->fire();
    }

    Enemy* Enemy::CreateGrunt(const glm::vec2 &position)
    {
        glm::vec2 size(50, 50);
        glm::vec2 velocity(0, 0);
        SDL_Surface* image = Resources::instance()["legs"];
        int hitpoints = 25;
        int armor = 0;
        int max_health = 25;
        int max_armor = 0;
        int weapon_type = WeaponType::SMG;

        Enemy* enemy = new Enemy(position, size, velocity, image, hitpoints, armor, max_health, max_armor, weapon_type);
        enemy->setAnimated(4, 8);
        enemy->setTopImage(Resources::instance()["grunt-torso"], 2, 25);

        return enemy;
    }

    Enemy* Enemy::CreateHeavy(const glm::vec2 &position)
    {
        return nullptr;
    }
}
