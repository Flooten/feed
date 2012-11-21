/*
 * FILNAMN:       mainmenu.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 */

#include "mainmenu.h"
#include "button.h"
#include "messagequeue.h"

#include <iostream>

namespace feed
{
    MainMenu::MainMenu(SDL_Surface* background, const glm::vec2& position)
        : main_(background, position)
    {}

    void MainMenu::draw(SDL_Surface* screen)
    {
        main_.draw(screen);
    }

    void MainMenu::update()
    {

    }

    void MainMenu::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE)
                    MessageQueue::instance().pushMessage({MessageQueue::Message::NEW_GAME, 0, 0});
                break;

            default:
                break;
        }
    }

    void MainMenu::handleMessage(const MessageQueue::Message& msg)
    {
        switch (msg.type)
        {
            default:
                break;
        }
    }
}
