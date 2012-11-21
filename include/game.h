/*
 * FILNAMN:       gameworld.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 * BESKRIVNING:   Huvudklassen för FEED. Ansvarar för SDL, resurser och "game-state".
 *
 */

#ifndef FEED_GAMEWORLD_H
#define FEED_GAMEWORLD_H

#include "mainmenu.h"
#include "world.h"
#include "messagequeue.h"

#include <SDL/SDL.h>
#include <stack>
#include <map>
#include <string>

namespace feed
{
    class Game
    {
    public:
        Game();
        ~Game();

        void run();

    private:
        void initSDL();
        void loadResources();
        void initMenu();
        void initWorld();
        void handleSDLEvent(const SDL_Event& event);
        void handleMessage(const MessageQueue::Message& msg);

        std::stack<State*> game_state_;
        std::map<std::string, SDL_Surface*> image_list_;

        SDL_Surface* screen_;

        bool running_ = true;
    };
}

#endif
