/*
 * FILNAMN:       animation.h
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-23
 *
 * BESKRIVNING: Denna klass agerar wrapper åt SDL_Surface
 *              om föremålet eller karaktären skall ha möjlighet
 *              att animeras.
 *
 */

#include <SDL/SDL.h>
#include <glm/glm.hpp>

namespace feed
{
    class AnimatedImage
    {
    public:
        AnimatedImage(SDL_Surface* image);

        void setAnimation(unsigned int index);
        void setAnimated(unsigned int nof_animations, unsigned int nof_frames);

        void update(unsigned int time);
        void draw(SDL_Surface* screen, const glm::vec2 position);

    private:
        SDL_Surface* image_sheet_;
        bool animated = false;
        const unsigned int FPS = 15;
        unsigned int last_draw_ = 0;   // Tid sedan senaste utritning
        unsigned short int frame_width_ = 0;
        unsigned short int frame_height_ = 0;
        unsigned short int nof_animations_ = 0;
        unsigned short int nof_frames_ = 0;
        unsigned short int current_animation_ = 0;
        unsigned short int current_frame_ = 0;
        SDL_Rect clip_ = {0, 0, 0, 0};

        void advanceFrame();
    };
}
