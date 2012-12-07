/*
 * FILNAMN:       mainmenu.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson 910322-1371 Y3A
 *                Mattias Fransson
 * DATUM:         2012-11-22
 *
 */

#include "mainmenu.h"
#include "button.h"
#include "messagequeue.h"
#include "resources.h"
#include "util.h"

#include <iostream>

namespace feed
{
    MainMenu::MainMenu(SDL_Surface* background, const glm::vec2& position)
        : main_(background, position)
    {
        // Temporär lösning, bilderna skall komma ifrån image_list_ egentligen.
        main_.addButton(new Button(Resources::instance().getImage("button_new_game"), Button::NEW_GAME));
        main_.addButton(new Button(Resources::instance().getImage("button_load_game"), Button::LOAD_GAME));
        main_.addButton(new Button(Resources::instance().getImage("button_credits"), Button::CREDITS));
        main_.addButton(new Button(Resources::instance().getImage("button_quit_game"), Button::QUIT_GAME));
    }

    void MainMenu::draw(SDL_Surface* screen)
    {
        util::blitSurface(Resources::instance()["screen_bg"], screen, 0, 0);
        main_.draw(screen);
    }

    void MainMenu::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE)
                    MessageQueue::instance().pushMessage({MessageQueue::Message::NEW_GAME, 0, 0});
                break;

            case SDL_MOUSEMOTION:
                main_.handleMouseMotionEvent(event.motion);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    main_.handleMouseButtonEvent(event.button);
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
