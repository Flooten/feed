/*
 * FILNAMN:       button.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 * BESKRIVNING: En knapp tillåter användaren att komma
 *              åt funktionalitet i spelet.
 *
 */

#ifndef FEED_BUTTON_H
#define FEED_BUTTON_H

#include <SDL/SDL.h>
#include <glm/glm.hpp>

namespace feed
{
    class Button
    {
    public:
        enum Type
        {
            INVALID,
            NEW_GAME,
            LOAD_GAME,
            QUIT_GAME
        };

        // Dimensioner
        static const int WIDTH = 250;
        static const int HEIGHT = 100;

        Button(SDL_Surface* background, const Type type);

        // Setters
        void set_position(const glm::vec2& position);

        void pressed() const;
        void mouseEntered();
        void mouseLeft();
        bool isMouseOver(const glm::vec2& mouse_position);
        void draw(SDL_Surface* screen);

    private:
        SDL_Surface* background_ = nullptr;
        SDL_Rect clip_[2];                     // 0 är inaktiv och 1 är aktiv.
        SDL_Rect position_ = {0, 0, 0, 0};     // Knappens absoluta position
        bool active_ = false;
        int type_ = 0;

        void initClips();                      // Initialiserar clips.
    };
}

#endif
