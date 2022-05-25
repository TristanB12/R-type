/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Sprite
*/

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"

namespace gui {
class Sprite : public AComponent {
public:
    using Ptr = std::shared_ptr<Sprite>;

    Sprite(const sf::Texture &texture) :
        m_sprite(texture)
    {}
    Sprite(const sf::Texture &texture, const sf::IntRect &textureRect) :
        m_sprite(texture, textureRect)
    {}
    virtual ~Sprite(void) = default;

    virtual bool isSelectable(void) const override
    {
        return false;
    }
    virtual void handleEvent(const sf::Event &event)
    {
        (void)event;
    }
    virtual sf::Vector2u getSize(void) const override
    {
        return boundsToSize(m_sprite.getGlobalBounds());
    }

    void setTextureRect(const sf::IntRect &textureRect)
    {
        m_sprite.setTextureRect(textureRect);
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
    }

    sf::Sprite m_sprite;
};
} // namespace gui

