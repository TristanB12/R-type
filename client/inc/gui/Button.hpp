/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Button
*/

#pragma once

#include <functional>
#include "RessourceManager.hpp"
#include "AComponent.hpp"
#include "Utils.hpp"
#include "Container.hpp"
#include "Label.hpp"

namespace gui {
class Button : public AComponent {
public:
    typedef std::shared_ptr<Button> Ptr;
    typedef std::function<void()> Callback;

    Button(const std::string &text, RessourceManager &ressourceManager) :
        m_text(std::make_shared<Label>(text, ressourceManager.getDefaultFont(), 16)),
        m_idleTexture(ressourceManager.getTexture("ButtonIdle")),
        m_selectedTexture(ressourceManager.getTexture("ButtonSelected")),
        m_pressedTexture(ressourceManager.getTexture("ButtonPressed")),
        m_sprite(m_idleTexture),
        m_container(boundsToSize(m_sprite.getGlobalBounds()))
    {
        m_text->setAlignement(VerticalAlignement::CENTER, HorizontalAlignement::CENTER);
        m_container << m_text;
    }

    virtual bool isSelectable() const override
    {
        return true;
    }
    virtual void select(void) override
    {
        AComponent::select();
        m_sprite.setTexture(m_selectedTexture);
        m_sprite.setScale(sf::Vector2f(1.2f, 1.2f));
        m_container.setScale(sf::Vector2f(1.2f, 1.2f));
    }

    virtual void deselect(void) override
    {
        AComponent::deselect();
        m_sprite.setTexture(m_idleTexture);
        m_sprite.setScale(sf::Vector2f(1, 1));
        m_container.setScale(sf::Vector2f(1, 1));
    }

    virtual void activate(void) override
    {
        AComponent::activate();
        if (m_callback) {
            m_callback();
        }
    }

    virtual void handleEvent(const sf::Event &event)
    {
        (void)event;
    }

    virtual sf::Vector2u getSize(void) const override
    {
        return m_container.getSize();
    }

    void setCallback(Callback callback)
    {
        m_callback = std::move(callback);
    }
    void setText(const std::string &text)
    {
        m_text->setText(text);
    }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
        target.draw(m_container, states);
    }

    Callback m_callback;
    std::shared_ptr<Label> m_text;
    const sf::Texture &m_idleTexture;
    const sf::Texture &m_selectedTexture;
    const sf::Texture &m_pressedTexture;
    sf::Sprite m_sprite;
    Container m_container;
};
} // namespace gui