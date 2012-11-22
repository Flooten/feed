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
#include <vector>

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
        void loadWorldList();
        void loadMenu();
        void loadWorld();
        void handleSDLEvent(const SDL_Event& event);
        void handleMessage(const MessageQueue::Message& msg);

        std::stack<State*> game_state_;
        std::vector<std::string> world_list_;
        std::size_t current_world_ = 0;

        SDL_Surface* screen_;

        bool running_ = true;
    };
}

#endif
