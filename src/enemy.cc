/*
 * FILNAMN:       enemy.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 */

#include "enemy.h"
#include "messagequeue.h"
#include "resources.h"
#include "util.h"

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
                 int weapon_type,
                 const glm::vec2& boundary_start,
                 const glm::vec2& boundary_end)
        : Character(position, size, velocity, image, hitpoints, armor, max_health, max_armor)
        , boundary_start_(boundary_start)
        , boundary_end_(boundary_end)
        , old_vel_(velocity)
    {
        weapon_ = Weapon::createWeapon(weapon_type);
        weapon_->set_max_ammo(-1);
        weapon_->set_max_clip(-1);

        if(boundary_end != glm::vec2(0,0))
        {
            velocity_.x = abs(velocity.x) * glm::normalize(boundary_end - boundary_start).x;
            walking = true;
            facing_right = true;
        }   
    }

    Enemy::~Enemy()
    {
        delete weapon_;
    }

    glm::vec2 Enemy::get_aim() const
    {
        return util::randomizeVec2(aim_, 0.1f);
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

    bool Enemy::get_previous_seen_state() const
    {
        return previous_seen_state_;
    }

    void Enemy::set_previous_seen_state(bool value)
    {
        previous_seen_state_ = value;
    }

    const Weapon* Enemy::get_weapon() const
    {
        return weapon_;
    }

    void Enemy::update(float delta_time)
    {
        set_seen_player(true);
        weapon_->update(delta_time);

        if (boundary_end_ != glm::vec2(0,0) && isWalking())
        {
            if (position_.x + size_.x >= boundary_end_.x && isFacingRight())
            {
                walkLeft();
            }
                    
            else if (position_.x <= boundary_start_.x && !isFacingRight())
            {
                walkRight();
            }
        }

         if(velocity_.y > 1000)
            MessageQueue::instance().pushMessage({MessageQueue::Message::ENEMY_DEAD, 0, this});

        Character::update(delta_time);
    }

    void Enemy::walkLeft()
    {
        setAnimation(Character::WALKING_LEFT);
        velocity_.x = -abs(velocity_.x);
        facing_right = false;
    }

    void Enemy::walkRight()
    {
        setAnimation(Character::WALKING_RIGHT);
        velocity_.x = abs(velocity_.x); //glm::length(velocity_)*glm::normalize(boundary_end_ - boundary_start_);
        facing_right = true;
    }

    bool Enemy::isWalking() const
    {
        return walking;
    }

    bool Enemy::isFacingRight() const
    {
        return facing_right;
    }

    void Enemy::stopWalking()
    {
        walking = false;
        old_vel_ = velocity_;
        velocity_ = glm::vec2(0, old_vel_.y);
    }

    void Enemy::continueWalking()
    {
        if(boundary_end_.x != 0)
        {
            walking = true;
            velocity_ = old_vel_;
            old_vel_ = glm::vec2(0,old_vel_.y);

            if (velocity_.x > 0)
                walkRight();
            else if (velocity_.x < 0)
                walkLeft();
        }
    }

    void Enemy::turn()
    {
        if (isWalking() && isFacingRight())
            walkLeft();
        else if (isWalking() && !isFacingRight())
            walkRight();
        else if (!isWalking() && isFacingRight())
        {
            setAnimation(Character::STATIONARY_LEFT);
            facing_right = false;
        }
        else if (!isWalking() && !isFacingRight())
        {
            setAnimation(Character::STATIONARY_RIGHT);
            facing_right = true;
        }

        previous_seen_state_ = false;
    }

    bool Enemy::isHit() const
    {
        return hit_;
    }

    void Enemy::set_hit(bool val)
    {
        hit_ = val;
    }

    ////////////////////////
    // Protected

    void Enemy::isDead()
    {
        MessageQueue::instance().pushMessage({MessageQueue::Message::ENEMY_DEAD, 0, this});
    }

    ////////////////////////
    // "Factory"-funktioner

    Enemy* Enemy::createGrunt(const glm::vec2& position, const glm::vec2& boundary_start, const glm::vec2& boundary_end)
    {
        glm::vec2 size(30, 110);
        glm::vec2 velocity;

        if (boundary_end != glm::vec2(0, 0))
            velocity.x = 50 ;

        SDL_Surface* image = Resources::instance()["legs"];
        int hitpoints = 25;
        int armor = 0;
        int max_health = 25;
        int max_armor = 0;
        int weapon_type = Weapon::ENEMY_PISTOL;

        Enemy* enemy = new Enemy(position, size, velocity, image, hitpoints, armor, max_health, max_armor, weapon_type, boundary_start, boundary_end);
        enemy->setAnimated(4, 8);
        enemy->setTopImage(Resources::instance()["grunt-torso"], 2, 37);
        enemy->set_collision_offset(glm::vec2(50, 40));

        if (velocity.x > 0)
            enemy->setAnimation(Character::WALKING_RIGHT);
        else if (velocity.x < 0)
            enemy->setAnimation(Character::WALKING_LEFT);
        else 
            enemy->setAnimation(Character::STATIONARY_LEFT);

        return enemy;
    }

    Enemy* Enemy::createHeavy(const glm::vec2 &position, const glm::vec2& boundary_start, const glm::vec2& boundary_end)
    {
        glm::vec2 size(30, 110);
        glm::vec2 velocity;

        if (boundary_end != glm::vec2(0, 0))
            velocity.x = 50;

        SDL_Surface* image = Resources::instance()["legs-dark"];
        int hitpoints = 50;
        int armor = 10;
        int max_health = 50;
        int max_armor = 10;
        int weapon_type = Weapon::SHOTGUN;

        Enemy* enemy = new Enemy(position, size, velocity, image, hitpoints, armor, max_health, max_armor, weapon_type, boundary_start, boundary_end);
        enemy->setAnimated(4, 8);
        enemy->setTopImage(Resources::instance()["heavy-torso"], 2, 37);
        enemy->set_collision_offset(glm::vec2(50, 40));

        if (velocity.x > 0)
            enemy->setAnimation(Character::WALKING_RIGHT);
        else if (velocity.x < 0)
            enemy->setAnimation(Character::WALKING_LEFT);
        else 
            enemy->setAnimation(Character::STATIONARY_LEFT);

        return enemy;
    }
}
