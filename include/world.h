/*
 * FILNAMN:       world.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 * BESKRIVNING:   World representerar en bana
 *
 */

#ifndef FEED_WORLD_H
#define FEED_WORLD_H

#include "state.h"
#include "enemy.h"
#include "projectile.h"
#include "interactableobject.h"
#include "environmentobject.h"
#include "player.h"

#include <vector>

namespace feed
{
    class World : public State
    {
    public:
        World();
        ~World();

        virtual void draw(SDL_Surface* screen) override final;
        virtual void update() override final;
        virtual void handleSDLEvent(const SDL_Event& event) override final;
        virtual void handleMessage(const MessageQueue::Message& msg) override final;

    private:
        Player* player_ = nullptr;

        std::vector<Projectile*> projectile_list_;
        std::vector<Enemy*> enemy_list_;
        std::vector<EnvironmentObject*> envobject_list_;
        std::vector<InteractableObject*> intobject_list_;
    };
}

#endif
