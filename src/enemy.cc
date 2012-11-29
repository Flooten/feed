/*
 * FILNAMN:       enemy.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 *                Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-26
 *
 */

#include "enemy.h"
#include "messagequeue.h"
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
    {
        weapon_ = Weapon::CreateWeapon(weapon_type, 100);
    }

    Enemy::~Enemy()
    {
        delete weapon_;
    }

    void Enemy::fire()
    {
        if (weapon_ != nullptr)
            if (weapon_->isReady())
            {
                MessageQueue::instance().pushMessage({MessageQueue::Message::FIRE, weapon_->get_type(), this});
                weapon_->fired();
            }
    }

    bool Enemy::get_seen_player() const
    {
        return seen_player_;
    }

    void Enemy::set_seen_player(bool value)
    {
        seen_player_ = value;
    }

    void Enemy::update(float delta_time)
    {
        set_seen_player(true);
        weapon_->update(delta_time);

        Character::update(delta_time);
    }

    Enemy* Enemy::CreateGrunt(const glm::vec2 &position)
    {
        glm::vec2 size(90, 130);
        glm::vec2 velocity(0, 0);
        SDL_Surface* image = Resources::instance()["legs"];
        int hitpoints = 25;
        int armor = 0;
        int max_health = 25;
        int max_armor = 0;
        int weapon_type = Weapon::ENEMY_PISTOL;

        Enemy* enemy = new Enemy(position, size, velocity, image, hitpoints, armor, max_health, max_armor, weapon_type);
        enemy->setAnimated(4, 8);
        enemy->setTopImage(Resources::instance()["grunt-torso"], 2, 37);

        return enemy;
    }

    Enemy* Enemy::CreateHeavy(const glm::vec2 &position)
    {
        return nullptr;
    }
}
