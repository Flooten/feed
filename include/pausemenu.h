/*
 * FILNAMN:       pausemenu.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING: En pausmeny visas när spelet är igång och spelaren
 *              trycker på ESC.
 *
 */


#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include "state.h"
#include "menu.h"

namespace feed
{
    class PauseMenu : public State
    {
    public:
        PauseMenu(SDL_Surface* background, SDL_Surface* menu_bg, const glm::vec2& position);
        ~PauseMenu();

        void draw(SDL_Surface* screen) override final;
        void update(float) {}
        void handleSDLEvent(const SDL_Event& event);
        void handleMessage(const MessageQueue::Message& msg);

    private:
        SDL_Surface* background_;
        Menu menu_;
    };
}
