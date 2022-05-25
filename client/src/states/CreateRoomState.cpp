/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** CreateRoomState
*/

#include "CreateRoomState.hpp"
#include "TextField.hpp"
#include "Label.hpp"
#include "StackPanel.hpp"
#include "Button.hpp"
#include "StateManager.hpp"

CreateRoomState::CreateRoomState(SharedContext &context) :
    AMenuState(context, "CreateRoom.conf")
{
    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("GoBackButton")
    )->setCallback([this] () {
        m_context.stateManager.navigate(States::ID::Menu);
    });

    auto stackPanel = std::dynamic_pointer_cast<gui::StackPanel>(
        AMenuState::getComponent("MyStackPanel")
    );

    std::dynamic_pointer_cast<gui::Label>(
        AMenuState::getComponent("RoomNameLabel")
    );

    m_roomNameField = std::dynamic_pointer_cast<gui::TextField>(
        stackPanel->getComponent("RoomNameField")
    );

    std::dynamic_pointer_cast<gui::Button>(
        stackPanel->getComponent("CreateRoomButton")
    )->setCallback([this] () {
        if (m_roomNameField->getText().empty()) {
            return;
        }
        Packet<rtype::Protocol> request(rtype::Protocol::CREATE_ROOM);
        char roomName[MAX_ROOM_NAME_LEN + 1] = "";
        std::strncpy(roomName, m_roomNameField->getText().c_str(), MAX_ROOM_NAME_LEN);
        request << roomName;
        m_context.network.send(request);
    });
    SET_TCP_HANDLER(CREATE_ROOM, onCreateRoom);
}

void CreateRoomState::onCreateRoom(Packet<rtype::Protocol> &response)
{
    int32_t roomID = 0;

    response >> roomID;
    if (roomID == -1) {
        std::cerr << "error creating room" << std::endl;
        return;
    }
    m_context.room = Room(roomID, m_roomNameField->getText(), 1);
    m_context.stateManager.navigate(States::ID::Room);
}