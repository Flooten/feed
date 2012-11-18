/*
 * FILNAMN:       menu.cc
 * PROJEKT:       F.E.E.D.
 * PROGRAMMERARE: Marcus Eriksson 910322-1371 Y3A
 * DATUM:         2012-11-18
 *
 */

#include "mainmenu.h"
#include "button.h"
#include "util.h"

namespace feed
{
    Menu::Menu(SDL_Surface* background, const glm::vec2& position)
        : background_(background)
        , position_(position)
    {}

    Menu::~Menu()
    {
        for (auto button : button_list_)
            delete button;
    }

    void Menu::addButton(Button* button)
    {
        button_list_.push_back(button);
    }

    void Menu::removeButton(unsigned int index)
    {
        button_list_.erase(button_list_.begin() + index);
    }

    void Menu::draw(SDL_Surface* screen)
    {
        if (background_ != nullptr)
        {
            // Rita bakgrunden
            util::blitSurface(background_, screen, position_.x, position_.y);

            for (unsigned int i = 0; i < button_list_.size(); ++i)
            {
                // Räkna fram knappens position och rita
                button_list_.at(i)->draw(screen, calculateButtonPosition(i));
            }
        }
    }

    void Menu::handleMouseMotionEvent(const SDL_MouseMotionEvent& event)
    {
        Button* colliding_button = collidingButton(glm::vec2(event.x, event.y));

        if (colliding_button != nullptr)
        {

        }
    }

    void Menu::handleMouseButtonEvent(const SDL_MouseButtonEvent& event)
    {
        Button* colliding_button = collidingButton(glm::vec2(event.x, event.y));

        if (colliding_button != nullptr)
        {
            
        }
    }

    /* 
     *  Private
     */
    glm::vec2 Menu::calculateButtonPosition(unsigned int index) const
    {
        glm::vec2 position;

        position.x = position_.x + X_OFFSET;
        position.y = position_.y + Y_OFFSET + (Button::HEIGHT + Y_SPACING) * index;

        return position;
    }

    Button* Menu::collidingButton(const glm::vec2& position)
    {

    }
}
