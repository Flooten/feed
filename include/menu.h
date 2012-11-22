/*
 * FILNAMN:       menu.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-21
 *
 * BESKRIVNING: Välkomstmenyn består av de knappar som användaren
 *              navigerar med hjälp av.
 *
 */

#ifndef FEED_MENU_H
#define FEED_MENU_H

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <vector>

namespace feed
{
    class Button;

    class Menu
    {
    public:
        Menu(SDL_Surface* background, const glm::vec2& position);
        ~Menu() noexcept;

        void addButton(Button* button);
        void removeButton(unsigned int index);
        void handleMouseMotionEvent(const SDL_MouseMotionEvent& event) const;
        void handleMouseButtonEvent(const SDL_MouseButtonEvent& event) const;
        void draw(SDL_Surface* screen);

    private:
        SDL_Surface* background_ = nullptr;
        std::vector<Button*> button_list_;
        glm::vec2 position_;

        static const int X_OFFSET = 30;
        static const int Y_OFFSET = 70;
        static const int Y_SPACING = 20;

        glm::vec2 calculateButtonPosition(unsigned int index) const;
    };
}

#endif
