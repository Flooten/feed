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

    void Resources::clear()
    {
        for (auto& r : resources_)
            SDL_FreeSurface(r.second);
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

    SDL_Surface* Resources::getImage(const std::string& key)
    {
        return resources_[key];
    }

    SDL_Surface* Resources::operator[](const std::string& key)
    {
        return getImage(key);
    }

    bool Resources::imageExist(const std::string& key)
    {
        auto it = resources_.find(key);
        return it != resources_.end();
    }
}
