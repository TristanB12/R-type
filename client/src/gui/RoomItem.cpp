/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RoomItem
*/

#include "RoomItem.hpp"

namespace gui {
RoomItem::RoomItem(
    const struct Room &room,
    const sf::Font &font,
    const sf::Vector2u &size
) : AListItem(size),
    m_container(size),
    m_room(room),
    m_roomNameLabel(std::make_shared<gui::Label>(room.name, font)),
    m_nbPlayersLabel(std::make_shared<gui::Label>("10 players", font))
{
    m_roomNameLabel->setHorizontalAlignement(HorizontalAlignement::LEFT);
    m_roomNameLabel->setMarginLeft(20);

    m_nbPlayersLabel->setText(std::to_string(room.nbPlayers) + " player"
        + (room.nbPlayers > 1 ? "s" : "")
    );
    m_nbPlayersLabel->setHorizontalAlignement(HorizontalAlignement::RIGHT);
    m_nbPlayersLabel->setMarginRight(30);
    m_container << m_roomNameLabel << m_nbPlayersLabel;
}
} // namespace gui