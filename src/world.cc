/*
 * FILNAMN:       world.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 */

#include "world.h"
#include "util.h"

#include <iostream>
#include <algorithm>

namespace feed
{
    World::World()
    {
        std::cout << "World " << this << " online" << std::endl;
    }

    World::World(const std::string& filename)
    {
        std::cout << "Loading world " << filename << std::endl;
    }

    World::~World()
    {
        std::cout << "World " << this << " dead" << std::endl;

        delete player_;

        // std::remove_if(projectile_list_.begin(), projectile_list_.end(), util::deleteElement<Projectile>);
        // std::remove_if(enemy_list_.begin(), enemy_list_.end(), util::deleteElement<Enemy>);
        // std::remove_if(envobject_list_.begin(), envobject_list_.end(), util::deleteElement<EnvironmentObject>);
        // std::remove_if(intobject_list_.begin(), intobject_list_.end(), util::deleteElement<InteractableObject>);

        for (auto e : projectile_list_)
            delete e;

        for (auto e : enemy_list_)
            delete e;

        for (auto e : envobject_list_)
            delete e;

        for (auto e : intobject_list_)
            delete e;
    }

    void World::draw(SDL_Surface* screen)
    {
        for (auto projectile : projectile_list_)
            projectile->draw(screen);

        for (auto enemy : enemy_list_)
            enemy->draw(screen);

        for (auto envobject : envobject_list_)
            envobject->draw(screen);

        for (auto intobject : intobject_list_)
            intobject->draw(screen);

        std::cout << "Dt: " << loop << " ms" << std::endl;
    }

    void World::update(Uint32 delta_time)
    {
        for (auto projectile : projectile_list_)
            projectile->update(delta_time);

        for (auto enemy : enemy_list_)
            enemy->update(delta_time);

        for (auto envobject : envobject_list_)
            envobject->update(delta_time);

        for (auto intobject : intobject_list_)
            intobject->update(delta_time);

        loop = delta_time;
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        MessageQueue::instance().pushMessage({MessageQueue::Message::PAUSE_GAME, 0, 0});
                        break;

                    case SDLK_UP:
                        MessageQueue::instance().pushMessage({MessageQueue::Message::FIRE, 0, 0});
                        break;

                    default:
                        break;
                }
                break;
            }

            default:
                break;
        }   
    }

    void World::handleMessage(const MessageQueue::Message& msg)
    {
        switch (msg.type)
        {
            default:
                break;
        }
    }
}
