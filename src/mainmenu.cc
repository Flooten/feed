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
        // Lägg till knappen och beräkna dess utritningsposition
        button_list_.push_back(button);
        button->set_position(calculateButtonPosition(button_list_.size() - 1));
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

            // Rita alla knappar
            for (auto button : button_list_)
            {
                button->draw(screen);
            }
        }
    }

    void Menu::handleMouseMotionEvent(const SDL_MouseMotionEvent& event)
    {
        // Nollställ alla knappar
        for (auto button : button_list_)
            button->mouseLeft();

        // Hämta knappen som muspekaren är över
        Button* colliding_button = collidingButton(glm::vec2(event.x, event.y));

        if (colliding_button != nullptr)
            colliding_button->mouseEntered();
    }

    void Menu::handleMouseButtonEvent(const SDL_MouseButtonEvent& event)
    {
        Button* colliding_button = collidingButton(glm::vec2(event.x, event.y));

        if (colliding_button != nullptr)
            colliding_button->pressed();
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
        // Om innanför menyn
        if ((position.x > position_.x) &&
            (position.x < position_.x + background_->w) &&
            (position.y > position_.y) &&
            (position.y < position_.y + background_->h))
        {
            // Gå igenom alla knappar
            for (auto button : button_list_)
                if (button->isMouseOver(position))
                    return button;
        }

        return nullptr;
    }
}
