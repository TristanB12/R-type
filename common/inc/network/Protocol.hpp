/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#define MAX_ROOM_NAME_LEN       15
#define CREATE_ROOM_FAILURE     -1

namespace rtype {
enum class Protocol : uint8_t
{
    // Requests / Responses
    GET_ROOMS,     // Get list of all available (in lobby) rooms
    CREATE_ROOM,
    JOIN_ROOM,
    GET_ROOM_PLAYERS,
    LEAVE_ROOM,
    READY_UP,
    START_GAME,
    END_GAME,
    DISCONNECTED,
    PLAYER_JOIN_ROOM // EVENT : When another player joins the room
};

enum class IngameProtocol : uint8_t
{
    MOVE,
    SHOOT
};
}

#endif /* !PROTOCOL_HPP_ */
