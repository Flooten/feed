/*
 * FILNAMN:       util.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-11-16
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
        // Strängmanipulation
        std::string getFileExtension(const std::string& filename);

        // Laddningsfunktioner för bilder
        SDL_Surface* loadImage(const std::string& filename);
        SDL_Surface* loadBmp(const std::string& filename);

        // "Blittar" source på destination vid position (x, y).
        // Vid mer avancerade fall använd SDL_BlitSurface direkt.
        void blitSurface(SDL_Surface* source, SDL_Surface* destination, int x, int y);
        void blitSurface(SDL_Surface* source, glm::vec2 size, SDL_Surface* destination, glm::vec2 position);
    }
}

#endif
