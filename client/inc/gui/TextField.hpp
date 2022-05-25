/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** TextField
*/

#pragma once

#include <cctype>
#include "AComponent.hpp"
#include "Utils.hpp"

namespace gui {
class TextField : public AComponent {
public:
    using Ptr = std::shared_ptr<TextField>;

    TextField(unsigned int maxLength, const sf::Font &font);
    virtual ~TextField(void) = default;

    bool isSelectable(void) const override
    {
        return true;
    }

    void handleEvent(const sf::Event &event) override;

    virtual void select(void) override
    {
        AComponent::select();
        m_box.setOutlineColor(sf::Color::Blue);
    }

    virtual void deselect(void) override
    {
        AComponent::deselect();
        m_box.setOutlineColor(sf::Color(127, 127, 127));
    }

    const std::string getText(void) const
    {
        return m_string;
    }

    virtual sf::Vector2u getSize(void) const override
    {
        return boundsToSize(m_box.getGlobalBounds());
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_box, states);
        target.draw(m_text, states);
    }

    unsigned int m_maxLength = 0;
    sf::RectangleShape m_box;
    std::string m_string;
    sf::Text m_text;
};
} // namespac egui
