/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** JoinRoomState
*/

#pragma once

#include "AMenuState.hpp"
#include "StackPanel.hpp"
#include "Label.hpp"
#include "Protocol.hpp"

class JoinRoomState : public AMenuState {
public:
    JoinRoomState(SharedContext &context);
    virtual ~JoinRoomState(void) = default;

private:
    void onGetRooms(Packet<rtype::Protocol> &response);
    void onJoinRoom(Packet<rtype::Protocol> &response);

    gui::StackPanel::Ptr m_roomStackPanel = nullptr;
    gui::Label::Ptr m_statusLabel = nullptr;
};
