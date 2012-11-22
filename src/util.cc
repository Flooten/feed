/*
 * FILNAMN:       util.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-11-16
 *
 */

#include "util.h"
#include <SDL/SDL_image.h>

namespace feed
{
    namespace util
    {
        std::string getFileExtension(const std::string& filename)
        {
            std::size_t pos = filename.find_last_of('.');

            if (pos != std::string::npos)
                return filename.substr(pos + 1);

            return "";
        }

        SDL_Surface* loadImage(const std::string& filename)
        {
            SDL_Surface* image = IMG_Load(filename.c_str());

            if (image != nullptr)
                image = SDL_DisplayFormatAlpha(image);

            return image;
        }

        SDL_Surface* loadBmp(const std::string& filename)
        {
            SDL_Surface* image = SDL_LoadBMP(filename.c_str());

            if (image != nullptr)
                image = SDL_DisplayFormat(image);

            return image;
        }

        void blitSurface(SDL_Surface* source, SDL_Surface* destination, int x, int y)
        {
            SDL_Rect rect = { static_cast<Sint16>(x), static_cast<Sint16>(y), 0, 0 };
            SDL_BlitSurface(source, nullptr, destination, &rect);
        }

        template <class T>
        bool deleteAll(T* p)
        {
            delete p;
            return true;
        }
    }
}
