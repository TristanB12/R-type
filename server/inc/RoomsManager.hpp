/*
** EPITECH PROJECT, 2021
** r-type [WSL: Ubuntu]
** File description:
** RoomsManager
*/

#ifndef ROOMSMANAGER_HPP_
#define ROOMSMANAGER_HPP_

#include <vector>
#include <iostream>
#include <memory>
#include "Room.hpp"
#include "ServerError.hpp"

#define ROOM_MANAGER_SUCCESS    0
#define ROOM_MANAGER_FAILURE    -1

class RoomsManager {
public:
    using room_manager_state = int;
    inline RoomsManager() :
        m_index(42)
    {};
    inline ~RoomsManager() {};

    std::shared_ptr<Room> getRoomByName(const std::string &roomName);
    std::shared_ptr<Room> getRoomByID(int roomID);

    bool roomAlreadyExists(const std::string &roomName);
    bool isRoomReady(int roomID);
    bool isRoomReady(const std::string &roomID);
    size_t getNbRooms(void) const;
    std::vector<std::shared_ptr<Room>> getRooms(void) const;
    room_manager_state createRoom(const std::string &roomName);
    room_manager_state addPlayerToRoom(const std::string &roomName, std::shared_ptr<rtype::Client> player);
    room_manager_state removePlayerFromRoom(const std::string &roomName, std::shared_ptr<rtype::Client> player);
    void removeRoom(std::shared_ptr<Room> room);
private:
    int m_index;
    std::vector<std::shared_ptr<Room>> m_rooms;
};
#endif /* !ROOMSMANAGER_HPP_ */
