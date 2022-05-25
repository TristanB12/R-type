/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Player
*/

#pragma once

#include "AListItem.hpp"
#include "models/Player.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "Sprite.hpp"

namespace gui {
class PlayerItem : public AListItem {
public:
    using Ptr = std::shared_ptr<PlayerItem>;

    PlayerItem(
        const struct Player &player,
        bool isReady,
        const sf::Texture &spaceshipTexture,
        const sf::Font &font,
        const sf::Vector2u &size = sf::Vector2u{}
    );
    virtual ~PlayerItem(void) = default;

    int getID(void) const
    {
        return m_player.id;
    }

    struct Player getPlayer(void) const
    {
        return m_player;
    }

    void toggleReady(void)
    {
        m_isReady = !m_isReady;
        m_readyLabel->setText(m_isReady ? "Ready" : "Not ready");
    }

    void setColor(Player::Color color)
    {
        m_player.color = color;
        m_spaceshipSprite->setTextureRect(this->getSpaceshipTextureRect());
        m_colorLabel->setText("Player " + m_player.colorToString());
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        AListItem::draw(target, states);
        states.transform *= getTransform();
        target.draw(m_container, states);
    }

    sf::IntRect getSpaceshipTextureRect(void)
    {
        sf::Vector2i spaceshipSize(34, 17);
        sf::Vector2i spaceshipPosition(0,
            spaceshipSize.y * static_cast<int>(m_player.color));

        return sf::IntRect(spaceshipPosition, spaceshipSize);
    }

    Container m_container;
    struct Player m_player;
    bool m_isReady = false;
    Sprite::Ptr m_spaceshipSprite;
    Label::Ptr m_colorLabel;
    Label::Ptr m_readyLabel;
};
} // namespace gui
