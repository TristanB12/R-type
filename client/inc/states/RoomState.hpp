/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RoomState
*/

#pragma once

#include "AMenuState.hpp"
#include "StackPanel.hpp"
#include "PlayerList.hpp"

class RoomState : public AMenuState {
public:
    RoomState(SharedContext &context);
    virtual ~RoomState(void) = default;

private:
    void onGetRoomPlayers(Packet<rtype::Protocol> &response);
    void onPlayerJoinRoom(Packet<rtype::Protocol> &response);
    void onPlayerLeaveRoom(Packet<rtype::Protocol> &response);
    void onPlayerReadyUp(Packet<rtype::Protocol> &response);
    void onStartGame(Packet<rtype::Protocol> &response);

    gui::PlayerList::Ptr m_playerList = nullptr;
};
