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
#include <iostream>

namespace feed
{
    void World::draw(SDL_Surface* screen)
    {
        std::cout << "World number " << i << std::endl; 
    }

    void World::update()
    {
        ++i;
    }

    void World::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    MessageQueue::instance().pushMessage({MessageQueue::Message::QUIT_GAME, 0, 0});
                break;

                if (event.key.keysym.sym == SDLK_SPACE)
                    MessageQueue::instance().pushMessage({MessageQueue::Message::FIRE, 0, 0});
                break;

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
