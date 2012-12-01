/*
 * FILNAMN:       util.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Mattias Fransson
 * DATUM:         2012-11-16
 *
 */

#include "util.h"
#include <SDL/SDL_image.h>
#include <random>

#include <iostream>

namespace feed
{
    namespace util
    {
        namespace
        {
            static std::mt19937 rng(SDL_GetTicks());
        }

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

        void blitSurface(SDL_Surface* source, glm::vec2 size, SDL_Surface* destination, glm::vec2 position)
        {
            SDL_Rect srcrect;
            srcrect.w = size.x;
            srcrect.h = size.y;
            srcrect.x = 0;
            srcrect.y = 0;

            SDL_Rect destrect;
            destrect.x = position.x;
            destrect.y = position.y;

            SDL_BlitSurface(source, &srcrect, destination, &destrect);
        }

        glm::vec2 randomizeVec2(const glm::vec2& v, float amount)
        {
            std::normal_distribution<> dist(0.0f, amount);
            return glm::vec2(v.x + dist(rng), v.y + dist(rng));
        }

        float randomizeFloat(float f, float amount)
        {
            std::normal_distribution<> dist(0.0f, amount);
            return f + dist(rng);
        }

        glm::vec2 worldToScreen(const glm::vec2& world_coordinates, const glm::vec2& camera_position)
        {
            glm::vec2 screen(camera_position - glm::vec2(PLAYER_OFFSET_X, PLAYER_OFFSET_Y));
            return world_coordinates - screen;   
        }

        glm::vec2 screenToWorld(const glm::vec2& screen_coordinates, const glm::vec2& camera_position)
        {
            glm::vec2 world(screen_coordinates + camera_position);

            return world - glm::vec2(PLAYER_OFFSET_X, PLAYER_OFFSET_Y);
        }
    }
}
