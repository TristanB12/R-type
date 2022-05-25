/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** PlayerItem
*/

#include "PlayerItem.hpp"

namespace gui {
PlayerItem::PlayerItem(
    const struct Player &player,
    bool isReady,
    const sf::Texture &spaceshipTexture,
    const sf::Font &font,
    const sf::Vector2u &size
) : AListItem(size),
    m_container(size),
    m_player(player),
    m_isReady(isReady),
    m_spaceshipSprite(std::make_shared<Sprite>(spaceshipTexture)),
    m_colorLabel(std::make_shared<Label>("Player YELLOW", font)),
    m_readyLabel(std::make_shared<Label>("Not ready", font))
{
    m_spaceshipSprite->setTextureRect(this->getSpaceshipTextureRect());
    m_spaceshipSprite->setHorizontalAlignement(HorizontalAlignement::LEFT);
    m_spaceshipSprite->setMarginLeft(20);
    m_spaceshipSprite->setScale({ 2.0f, 2.0f });

    m_colorLabel->setMarginLeft(m_spaceshipSprite->getSize().x + 100);

    m_readyLabel->setHorizontalAlignement(HorizontalAlignement::RIGHT);
    m_readyLabel->setMarginRight(30);

    m_container.setChildrenVerticalAlignement(VerticalAlignement::CENTER);
    m_container << m_spaceshipSprite << m_colorLabel << m_readyLabel;

    m_readyLabel->setText(isReady ? "Ready" : "Not ready");
    m_colorLabel->setText("Player " + m_player.colorToString());
}
} // namespace gui
