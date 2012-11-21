/*
 * FILNAMN:       gameworld.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Herman Ekwall
 *                Marcus Eriksson
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 * BESKRIVNING: Spelet
 *
 */

#ifndef FEED_GAMEWORLD_H
#define FEED_GAMEWORLD_H

#include "player.h"
#include "mainmenu.h"
#include "enemy.h"
#include "projectile.h"
#include "interactableobject.h"
#include "environmentobject.h"
#include "messagequeue.h"

#include <SDL/SDL.h>
#include <vector>
#include <map>
#include <string>

namespace feed
{
    class GameWorld
    {
    public:
        GameWorld();
        ~GameWorld();

        void run();

    private:
        void initSDL();
        void loadResources();
        void initMenu();
        void initWorld();
        void draw();
        void handleSDLEvent(const SDL_Event& event);
        void handleMessage(const MessageQueue::Message& msg);

        Player* player_ = nullptr;
        Menu* main_menu_ = nullptr;
        Menu* pause_menu_ = nullptr;

        std::vector<Projectile*> projectile_list_;
        std::vector<Enemy*> enemy_list_;
        std::vector<EnvironmentObject*> envobject_list_;
        std::vector<InteractableObject*> intobject_list_;
        std::map<std::string, SDL_Surface*> image_list_;

        SDL_Surface* screen_;

        bool running_ = true;
        bool ismainmenu = true;
        bool paused_ = false;
    };
}

#endif
