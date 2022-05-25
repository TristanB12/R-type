/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** CreateRoomState
*/

#pragma once

#include "AMenuState.hpp"
#include "TextField.hpp"

class CreateRoomState : public AMenuState {
public:
    CreateRoomState(SharedContext &context);
    virtual ~CreateRoomState(void) = default;

private:
    void onCreateRoom(Packet<rtype::Protocol> &response);

    std::shared_ptr<gui::TextField> m_roomNameField = nullptr;
};
