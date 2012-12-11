/*
 * FILNAMN:       pausemenu.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 *          
 * DATUM:         2012-12-12
 *
 */

#include "pausemenu.h"
#include "button.h"
#include "util.h"
#include "resources.h"

namespace feed
{
    /*
     *  Public
     */
    PauseMenu::PauseMenu(SDL_Surface* background, SDL_Surface* menu_bg, const glm::vec2& position)
        : background_(SDL_ConvertSurface(background, background->format, SDL_SWSURFACE))
        , menu_(menu_bg, position)
    {
        // Lägg till knappar här
        menu_.addButton(new Button(Resources::instance().getImage("button_resume_game"), Button::RESUME_GAME));
        menu_.addButton(new Button(Resources::instance().getImage("button_load_game"), Button::LOAD_GAME));
        menu_.addButton(new Button(Resources::instance().getImage("button_exit_to_main_menu"), Button::EXIT_TO_MAIN_MENU));
    }

    PauseMenu::~PauseMenu()
    {
        SDL_FreeSurface(background_);
    }

    void PauseMenu::draw(SDL_Surface* screen)
    {
        if (background_ != nullptr && screen != nullptr)
        {
            util::blitSurface(background_, screen, 0, 0);
            menu_.draw(screen);
        }
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

            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    MessageQueue::instance().pushMessage({MessageQueue::Message::RESUME_GAME});
                break;
            }

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
