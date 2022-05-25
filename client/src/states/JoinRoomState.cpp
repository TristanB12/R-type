/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** JoinRoomState
*/

#include "JoinRoomState.hpp"
#include "StackPanel.hpp"
#include "RoomItem.hpp"
#include "Button.hpp"
#include "StateManager.hpp"
#include "Utils.hpp"

JoinRoomState::JoinRoomState(SharedContext &context) :
    AMenuState(context, "JoinRoom.conf")
{
    m_roomStackPanel = std::dynamic_pointer_cast<gui::StackPanel>(
        AMenuState::getComponent("RoomStackPannel")
    );

    m_statusLabel = std::dynamic_pointer_cast<gui::Label>(
        AMenuState::getComponent("StatusLabel")
    );

    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("GoBackButton")
    )->setCallback([this] () {
        m_context.stateManager.navigate(States::ID::Menu);
    });

    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("RefreshRoomsButton")
    )->setCallback([this] () {
        this->m_roomStackPanel->clear();
        this->m_statusLabel->setText("Loading...");
        m_context.network.send(rtype::Protocol::GET_ROOMS);
    });

    SET_TCP_HANDLER(GET_ROOMS, onGetRooms);
    SET_TCP_HANDLER(JOIN_ROOM, onJoinRoom);
    m_context.network.send(rtype::Protocol::GET_ROOMS);
}

void JoinRoomState::onGetRooms(Packet<rtype::Protocol> &response)
{
    sf::Vector2u roomItemSize = {
        calcPercentage(80U, m_context.window.getSize().x),
        100
    };

    while (response.getBodySize() > 0) {
        struct Room room;

        response >> room.nbPlayers >> room.name >> room.id;
        auto roomItem = std::make_shared<gui::RoomItem>(
            room,
            m_context.ressources.getDefaultFont(),
            roomItemSize
        );
        roomItem->setCallback([this, roomItem] ()
        {
            m_context.room = Room(roomItem->getRoom());
            Packet<rtype::Protocol> packet(rtype::Protocol::JOIN_ROOM);
            packet << roomItem->getID();
            m_context.network.send(packet);
        });
        *m_roomStackPanel << roomItem;
    }
    size_t nbRooms = m_roomStackPanel->getNbChildren();
    this->m_statusLabel->setText((nbRooms == 0) ?
        "No room available."
        : std::to_string(nbRooms) + " room" + ((nbRooms > 1) ? "s" : "") + " available"
    );
}

void JoinRoomState::onJoinRoom(Packet<rtype::Protocol> &response)
{
    bool joined = false;

    response >> joined;
    if (joined) {
        m_context.stateManager.navigate(States::ID::Room);
    }
}