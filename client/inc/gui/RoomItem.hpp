/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RoomItem
*/

#pragma once

#include "AListItem.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "Room.hpp"

namespace gui {
class RoomItem : public AListItem {
public:
    RoomItem(
        const struct Room &room,
        const sf::Font &font,
        const sf::Vector2u &size
    );
    virtual ~RoomItem(void) = default;

    operator Room(void) const
    {
        return m_room;
    }

    struct Room getRoom(void) const
    {
        return m_room;
    }

    int getID(void) const
    {
        return m_room.id;
    }

    uint8_t getNbPlayers(void) const
    {
        return m_room.nbPlayers;
    }

    std::string getName(void) const
    {
        return std::string(m_room.name);
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        AListItem::draw(target, states);
        states.transform *= getTransform();
        target.draw(m_container);
    }

    gui::Container m_container;
    struct Room m_room;
    gui::Label::Ptr m_roomNameLabel;
    gui::Label::Ptr m_nbPlayersLabel;
}; // class RoomItem
} // namespace gui