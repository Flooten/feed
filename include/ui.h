/*
 * FILNAMN:       ui.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Joel Davidsson
 * DATUM:         2012-11-29
 *
 * BESKRIVNING: 
 *
 */

#ifndef FEED_UI_H
#define FEED_UI_H

#include <SDL/SDL.h>
#include <glm/glm.hpp>

namespace feed
{
    class Ui
    {
    public:
        Ui(class Player* player, SDL_Surface* image, SDL_Surface* health_bar, SDL_Surface* armor_bar);
        ~Ui() = default;

        void update();
        void draw(SDL_Surface* screen);

    private:
        Player* player_;

        glm::vec2 ui_pos_ = glm::vec2(0,475);
        glm::vec2 ui_size_ = glm::vec2(1024,101);

        glm::vec2 health_bar_pos_ = glm::vec2(100,525);
        glm::vec2 armor_bar_pos_ = glm::vec2(200,525);

        glm::vec2 health_bar_size_ = glm::vec2(100,25);
        glm::vec2 armor_bar_size_ = glm::vec2(100,25);

        int clip_size_;
        int ammo_size_;

        SDL_Surface* ui_image_;
        SDL_Surface* health_bar_image_;
        SDL_Surface* armor_bar_image_;
    };
}

#endif
