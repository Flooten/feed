/*
 * FILNAMN:       resources.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 * DATUM:         2012-11-21
 *
 * BESKRIVNING:   Singleton för att hålla spelets bilder (resurser)
 *
 */

#ifndef FEED_RESOURCES_H
#define FEED_RESOURCES_H

#include <map>
#include <string>
#include <SDL/SDL.h>

namespace feed
{
    class Resources
    {
    public:
        static Resources& instance();

        void clear();

        bool addImage(const std::string& key, const std::string& filename);
        void removeImage(const std::string& key);

        SDL_Surface* getImage(const std::string& key);
        SDL_Surface* operator[](const std::string& key);

        bool imageExist(const std::string& key);

    private:
        Resources() = default;
        Resources(const Resources&) = delete;
        Resources(Resources&&) = delete;

        std::map<std::string, SDL_Surface*> resources_;
    };
}

#endif
