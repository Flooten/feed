/*
 * FILNAMN:       resources.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING:   Singleton för att hålla spelets bilder (resurser)
 *
 */

#ifndef FEED_RESOURCES_H
#define FEED_RESOURCES_H

#include <map>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

namespace feed
{
    class Resources
    {
    public:
        static Resources& instance();

        bool init();
        void clear();

        bool addImage(const std::string& key, const std::string& filename);
        void removeImage(const std::string& key);

        bool addFont(const std::string& key, const std::string& filename, int ptsize);
        void removeFont(const std::string& key);

        SDL_Surface* getImage(const std::string& key);
        SDL_Surface* operator[](const std::string& key);
        TTF_Font* getFont(const std::string& key);

        bool imageExist(const std::string& key);
        bool fontExists(const std::string& key);

    private:
        Resources() = default;
        Resources(const Resources&) = delete;
        Resources(Resources&&) = delete;

        std::map<std::string, SDL_Surface*> resources_;
        std::map<std::string, TTF_Font*> fonts_;
    };
}

#endif
