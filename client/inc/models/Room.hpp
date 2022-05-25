/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Room
*/

#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include "Protocol.hpp"
#include "Player.hpp"

struct Room {
    Room(void) = default;
    Room(int32_t id, const std::string &roomName, uint8_t nbPlayers) :
        id(id), nbPlayers(nbPlayers)
    {
        std::strncpy(this->name, roomName.c_str(), MAX_ROOM_NAME_LEN);
    }

    int32_t id;
    uint8_t nbPlayers;
    std::vector<struct Player> players;
    char name[MAX_ROOM_NAME_LEN + 1];
};
