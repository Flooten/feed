/*
 * FILNAMN:       ui.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 *                Marcus Eriksson
 * DATUM:         2012-12-12
 *
 * BESKRIVNING:   Användareinterface
 *
 */

#ifndef FEED_UI_H
#define FEED_UI_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <glm/glm.hpp>
#include "resources.h"

namespace feed
{
    class Ui
    {
    public:
        Ui(class Player* player, SDL_Surface* image, SDL_Surface* health_bar, SDL_Surface* armor_bar);

        void update();
        void draw(SDL_Surface* screen);

    private:
        Player* player_;

        glm::vec2 ui_pos_ = glm::vec2(0, 475);
        glm::vec2 ui_size_ = glm::vec2(1024, 101);

        glm::vec2 health_bar_pos_ = glm::vec2(100, 525);
        glm::vec2 armor_bar_pos_ = glm::vec2(200, 525);

        glm::vec2 health_bar_size_ = glm::vec2(100, 25);
        glm::vec2 armor_bar_size_ = glm::vec2(100, 25);

        glm::vec2 current_weapon_pos_ = glm::vec2(350, 500);
        glm::vec2 inventory_pos_ = glm::vec2(600, 500);

        glm::vec2 clip_text_pos_ = glm::vec2(450, 500);
        glm::vec2 ammo_text_pos_ = glm::vec2(525, 525);

        int clip_size_;
        int ammo_size_;

        SDL_Surface* ui_image_ = nullptr;
        SDL_Surface* health_bar_image_ = nullptr;
        SDL_Surface* armor_bar_image_ = nullptr;
        SDL_Surface* clip_text_ = nullptr;
        SDL_Surface* ammo_text_ = nullptr;

        SDL_Color text_color_ = {255, 85, 0, 0};
    };
}

#endif
