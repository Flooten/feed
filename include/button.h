/*
 * FILNAMN:       button.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson
 * DATUM:         2012-12-12
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
            RESUME_GAME,
            LOAD_GAME,
            QUIT_GAME,
            EXIT_TO_MAIN_MENU,
            CREDITS
        };

        // Dimensioner
        static const int WIDTH = 300;
        static const int HEIGHT = 60;

        Button(SDL_Surface* background, const Type type);

        // Setters
        void set_position(const glm::vec2& position);

        void handleMouseMotionEvent(const SDL_MouseMotionEvent& event);
        void handleMouseButtonEvent(const SDL_MouseButtonEvent& event) const;
        void draw(SDL_Surface* screen);

    private:
        SDL_Surface* background_ = nullptr;
        SDL_Rect clip_[2];                     // 0 är inaktiv och 1 är aktiv.
        SDL_Rect position_ = {0, 0, 0, 0};     // Knappens absoluta position. Av typ
                                               // SDL_Rect för att underlätta utritning.
        bool active_ = false;
        int type_ = 0;

        void initClips();                      // Initialiserar clips.
        void pressed() const;
        void mouseEntered();
        void mouseLeft();
        bool mouseIsOver(int mouse_position_x, int mouse_position_y) const;
    };
}

#endif
