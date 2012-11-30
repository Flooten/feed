/*
 * FILNAMN:       util.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-11-26
 *
 * BESKRIVNING: Allmänna funktioner som inte direkt kan kopplas till en klass.
 *
 */

#ifndef FEED_UTIL_H
#define FEED_UTIL_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace feed
{
    namespace util
    {
        // util-konstanter
        const int PLAYER_OFFSET_X = 1024 * 0.382;
        const int PLAYER_OFFSET_Y = 576 * 0.618;
        const int PLAYER_MAX_HEALTH = 100;
        const int PLAYER_MAX_ARMOR = 100;
        const float JUMP_VELOCITY = -350.0f;
        const glm::vec2 GRAVITY = glm::vec2(0, 550.0f);

        const int SCREEN_WIDTH = 1024;
        const int SCREEN_HEIGHT = 576;
        

        // Strängmanipulation
        std::string getFileExtension(const std::string& filename);

        // Laddningsfunktioner för bilder
        SDL_Surface* loadImage(const std::string& filename);
        SDL_Surface* loadBmp(const std::string& filename);

        // "Blittar" source på destination vid position (x, y).
        // Vid mer avancerade fall använd SDL_BlitSurface direkt.
        void blitSurface(SDL_Surface* source, SDL_Surface* destination, int x, int y);
        void blitSurface(SDL_Surface* source, glm::vec2 size, SDL_Surface* destination, glm::vec2 position);

        // Slumpar riktningen v med mängden amount (normaldistribution med
        // med standardavvikelse amount)
        glm::vec2 randomizeVec2(const glm::vec2& v, float amount);
    }
}

#endif
