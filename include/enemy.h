/*
 * FILNAMN:       enemy.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-26
 *
 * BESKRIVNING: Denna klass definierar en fiende. Ärver från Character
 *
 */

#ifndef FEED_ENEMY_H
#define FEED_ENEMY_H

#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include "character.h"
#include "weapon.h"
#include "util.h"

namespace feed
{
    class Enemy : public Character
    {
    public:
        Enemy(const glm::vec2& position,
              const glm::vec2& size,
              const glm::vec2& velocity,
              SDL_Surface* image,
              int hitpoints,
              int armor,
              int max_health,
              int max_armor,
              int weapon_type,
              const glm::vec2& boundary_start  = glm::vec2(0,0),
              const glm::vec2& boundary_end = glm::vec2(0,0));
        ~Enemy();

        glm::vec2 get_aim() const override final;

        void fire();
        bool get_seen_player() const;
        void set_seen_player(bool value);

        bool get_previous_seen_state() const;
        void set_previous_seen_state(bool val);

        bool isWalking() const;
        bool isFacingRight() const;
        void walkLeft();
        void walkRight();
        void stopWalking();
        void continueWalking();
        void turn();



        bool isHit() const;
        void set_hit(bool val);

        void update(float delta_time) override;

        static Enemy* createGrunt(const glm::vec2& position, const glm::vec2& boundary_start = glm::vec2(0,0), const glm::vec2& boundary_end = glm::vec2(0,0));
        static Enemy* createHeavy(const glm::vec2& position, const glm::vec2& boundary_start = glm::vec2(0,0), const glm::vec2& boundary_end = glm::vec2(0,0));

    protected:
        void isDead() override final;

    private:
        Weapon* weapon_;
        bool seen_player_ = true;
        bool hit_ = false;
        bool previous_seen_state_ = false;
        bool walking = false;
        bool facing_right = true;
        glm::vec2 boundary_start_;
        glm::vec2 boundary_end_;

        glm::vec2 old_vel_;

    };
}

#endif
