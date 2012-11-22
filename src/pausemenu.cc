/*
 * FILNAMN:       pausemenu.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 *          
 * DATUM:         2012-11-22
 *
 */

#include "pausemenu.h"
#include "button.h"
#include "util.h"

namespace feed
{
    /*
     *  Public
     */
    PauseMenu::PauseMenu(SDL_Surface* background, const glm::vec2& position)
        : menu_(background, position)
    {
        // Lägg till knappar här
        menu_.addButton(new Button(util::loadImage("data/button_new_game.png"), Button::RESUME_GAME));
        menu_.addButton(new Button(util::loadImage("data/button_exit_game.png"), Button::QUIT_GAME));
    }

    void PauseMenu::draw(SDL_Surface* screen)
    {
        menu_.draw(screen);
    }

    void PauseMenu::handleSDLEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    menu_.handleMouseButtonEvent(event.button);
                break;

            case SDL_MOUSEMOTION:
                menu_.handleMouseMotionEvent(event.motion);
                break;

            default:
                break;
        }
    }

    void PauseMenu::handleMessage(const MessageQueue::Message& msg)
    {
        switch (msg.type)
        {
            default:
                break;
        }
    }
}
