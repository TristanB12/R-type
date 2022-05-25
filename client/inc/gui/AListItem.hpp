/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ListItem
*/

#pragma once

#include "AComponent.hpp"
#include "Utils.hpp"

namespace gui {
class AListItem : public AComponent {
public:
    typedef std::function<void()> Callback;

    virtual ~AListItem(void) = default;

    virtual bool isSelectable(void) const override
    {
        return m_callback ? true : false;
    }

    virtual void select(void) override
    {
        AComponent::select();
        m_box.setFillColor(sf::Color(0, 0, 0, 120));
    }

    virtual void deselect(void) override
    {
        AComponent::deselect();
        m_box.setFillColor(sf::Color(0, 0, 0, 190));
    }

    virtual void activate(void) override
    {
        AComponent::activate();
        if (m_callback) {
            m_callback();
        }
    }

    virtual void handleEvent(const sf::Event &event) override
    {
        (void)event;
    }

    virtual sf::Vector2u getSize(void) const override
    {
        return boundsToSize(m_box.getGlobalBounds());
    }

    void setCallback(Callback callback)
    {
        m_callback = std::move(callback);
    }

    void setSize(const sf::Vector2f &size)
    {
        m_box.setSize(size);
    }

protected:
    AListItem(const sf::Vector2u &size = sf::Vector2u{0, 0}) :
        m_box(sf::Vector2f(size))
    {
        m_box.setOutlineThickness(2.0f);
        m_box.setOutlineColor(sf::Color(127, 127, 127));
        m_box.setFillColor(sf::Color(0, 0, 0, 190));
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_box, states);
    }

private:
    Callback m_callback;
    sf::RectangleShape m_box;
};

} // namespace gui
