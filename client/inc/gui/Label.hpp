/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Label
*/

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"
#include "RessourceManager.hpp"

namespace gui {
class Label : public AComponent {
public:
    using Ptr = std::shared_ptr<Label>;

    Label(const std::string &text, const sf::Font &font, unsigned int characterSize = 30U) :
        m_text(text, font, characterSize)
    {}
    Label(const std::string &text, RessourceManager &ressources, unsigned int characterSize = 30U) :
        m_text(text, ressources.getDefaultFont(), characterSize)
    {}
    virtual bool isSelectable(void) const override
    {
        return false;
    }
    void setText(const std::string &text)
    {
        m_text.setString(text);
    }
    void setColor(const sf::Color &color)
    {
        m_text.setFillColor(color);
    }

    virtual void handleEvent(const sf::Event &event)
    {
        (void)event;
    }

    virtual sf::Vector2u getSize(void) const override
    {
        return boundsToSize(m_text.getGlobalBounds());
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_text, states);
    }

    sf::Text m_text;
};
} // namespace gui