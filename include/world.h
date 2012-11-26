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

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace feed
{
    class World : public State
    {
    public:
        World();
        World(const std::string& filename);

        ~World();

        virtual void draw(SDL_Surface* screen) override final;
        virtual void update(float delta_time) override final;
        virtual void handleSDLEvent(const SDL_Event& event) override final;
        virtual void handleMessage(const MessageQueue::Message& msg) override final;

    private:
        void loadImage(const std::string& str);
        void loadAudio(const std::string& str);
        void loadProjectile(const std::string& str);
        void loadEnemy(const std::string& str);
        void loadPlayer(const std::string& str);
        void loadEnvironmentObject(const std::string& str);
        void loadInteractableObject(const std::string& str);

        bool collision(const Object* obj1, const Object* obj2);
        bool line_of_sight(const Enemy* enemy, const Player* player);

        Player* player_ = nullptr;

        std::vector<Projectile*> projectile_list_;
        std::vector<Enemy*> enemy_list_;
        std::vector<EnvironmentObject*> envobject_list_;
        std::vector<InteractableObject*> intobject_list_;

        glm::vec2 camera_position_;

        Uint32 loop;
    };
}

#endif
