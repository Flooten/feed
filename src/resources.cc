/*
 * FILNAMN:       resources.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Herman Ekwall
 *                Mattias Fransson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING:   Singleton för att hålla spelets bilder (resurser)
 *
 */

#include "resources.h"
#include "util.h"

#include <utility>

namespace feed
{
    Resources& Resources::instance()
    {
        static Resources instance_;
        return instance_;
    }

    bool Resources::init()
    {
        return !(TTF_Init() == -1);
    }

    void Resources::clear()
    {
        for (auto& r : resources_)
            SDL_FreeSurface(r.second);

        for (auto& f : fonts_)
            TTF_CloseFont(f.second);

        TTF_Quit();
    }

    bool Resources::addImage(const std::string& key, const std::string& filename)
    {
        if (imageExist(key))
            removeImage(key);

        SDL_Surface* image = util::loadImage(filename);

        if (image == nullptr)
            return false;

        resources_.insert(std::make_pair(key, image));

        return true;
    }

    void Resources::removeImage(const std::string& key)
    {
        SDL_FreeSurface(resources_[key]);
        resources_.erase(key);
    }

    bool Resources::addFont(const std::string& key, const std::string& filename, int ptsize)
    {
        if (fontExists(key))
            removeFont(key);

        TTF_Font* font = TTF_OpenFont(filename.c_str(), ptsize);

        if (font == nullptr)
            return false;

        fonts_.insert(std::make_pair(key, font));

        return true;
    }

    void Resources::removeFont(const std::string& key)
    {
        TTF_CloseFont(fonts_[key]);
        fonts_.erase(key);
    }   

    SDL_Surface* Resources::getImage(const std::string& key)
    {
        return resources_[key];
    }

    SDL_Surface* Resources::operator[](const std::string& key)
    {
        return getImage(key);
    }

    TTF_Font* Resources::getFont(const std::string& key)
    {
        return fonts_[key];
    }

    bool Resources::imageExist(const std::string& key)
    {
        auto it = resources_.find(key);
        return it != resources_.end();
    }

    bool Resources::fontExists(const std::string& key)
    {
        auto it = fonts_.find(key);
        return it != fonts_.end();
    }
}
