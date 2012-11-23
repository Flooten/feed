/*
 * FILNAMN:       animation.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson   910322-1371     Y3A
 * DATUM:         2012-11-22
 *
 */

#include "animatedimage.h"
#include <iostream>

namespace feed
{
    /*
     *  Public
     */

    AnimatedImage::AnimatedImage(SDL_Surface* image, unsigned int nof_animations, unsigned int nof_frames)
        : image_sheet_(image)
        , nof_animations_(nof_animations)
        , nof_frames_(nof_frames)
    {
        if ((nof_animations_ == 0) && (nof_frames_== 0))
            animated = false;
        else
        {
            frame_width_ = image->w / nof_animations;
            frame_height_ = image->h / nof_frames;
        }
    }

    void AnimatedImage::setAnimation(unsigned int index)
    {
        // Om ett giltigt index
        if (index < nof_animations_)
            current_animation_ = index;
    }

    void AnimatedImage::setAnimated(unsigned int nof_animations, unsigned int nof_frames)
    {
        animated = true;
        nof_animations_ = nof_animations;
        nof_frames_ = nof_frames;
    }

    void AnimatedImage::update(unsigned int time)
    {
        if (animated)
        {
            unsigned int elapsed_time = time + last_draw_;

            if (elapsed_time >= 1000 / FPS)
            {
                // Dags att byta frame
                advanceFrame();

                // Uppdatera tiden
                last_draw_ = elapsed_time - 1000 / FPS;
            }
            else
            {
                last_draw_ = elapsed_time;
            }
        }
    }

    void AnimatedImage::draw(SDL_Surface* screen, const glm::vec2 position)
    {
        SDL_Rect screen_position = {position.x, position.y, 0, 0};

        if (animated)
            SDL_BlitSurface(image_sheet_, &clip_, screen, &screen_position);
        else
            SDL_BlitSurface(image_sheet_, nullptr, screen, &screen_position);
    }

    /*
     *  Private
     */

    void AnimatedImage::advanceFrame()
    {
        if (animated)
        {
            if (current_frame_ == nof_frames_ - 1)
                // Börja om från början
                current_frame_ = 0;
            else
                // Avancera
                ++current_frame_;

            // Uppdatera clip
            clip_ = {frame_width_ * current_animation_,
                     frame_height_ * current_frame_,
                     frame_width_,
                     frame_height_};
        }
    }
}
