/*
** EPITECH PROJECT, 2021
** r-type [WSL: Ubuntu]
** File description:
** RoomsManager
*/

#include "RoomsManager.hpp"

#include "RoomsManager.hpp"

bool RoomsManager::roomAlreadyExists(const std::string &roomName) {
    for (auto &room : m_rooms) {
        if (room->getRoomName() == roomName)
            return true;
    }
    return false;
}

std::shared_ptr<Room> RoomsManager::getRoomByName(const std::string &roomName) {
    for (auto &room : m_rooms) {
        if (room->getRoomName() == roomName)
            return room;
    }
    return nullptr;
}

std::shared_ptr<Room> RoomsManager::getRoomByID(int roomID) {
    for (auto &room : m_rooms) {
        if (room->getId() == roomID)
            return room;
    }
    return nullptr;
}

RoomsManager::room_manager_state RoomsManager::createRoom(const std::string &roomName) {
    if (roomAlreadyExists(roomName))
        return ROOM_MANAGER_FAILURE;
    m_rooms.push_back(std::make_shared<Room>(roomName, m_index));
    m_index++;
    return m_index - 1;
}

RoomsManager::room_manager_state RoomsManager::addPlayerToRoom(const std::string &roomName, std::shared_ptr<rtype::Client> player) {
    auto room = getRoomByName(roomName);

    if (!room)
        return ROOM_MANAGER_FAILURE;
    room->addPlayer(player);
    player->setRoomID(room->getId());
    return ROOM_MANAGER_SUCCESS;
}

RoomsManager::room_manager_state RoomsManager::removePlayerFromRoom(const std::string &roomName, std::shared_ptr<rtype::Client> player) {
    auto room = getRoomByName(roomName);

    if (!room)
        return ROOM_MANAGER_FAILURE;
    room->removePlayer(player);
    player->setRoomID(-1);
    if (room->getNbPlayer() == 0)
        removeRoom(room);
    return ROOM_MANAGER_SUCCESS;
}

bool RoomsManager::isRoomReady(int roomID) {
    auto room = getRoomByID(roomID);

    return room->isRoomReady();
}

bool RoomsManager::isRoomReady(const std::string &roomName) {
    auto room = getRoomByName(roomName);

    return room->isRoomReady();
}

size_t RoomsManager::getNbRooms(void) const {
    return m_rooms.size();
}

std::vector<std::shared_ptr<Room>> RoomsManager::getRooms(void) const {
    return m_rooms;
}

void RoomsManager::removeRoom(std::shared_ptr<Room> room) {
    m_rooms.erase(std::remove(m_rooms.begin(), m_rooms.end(), room));
}