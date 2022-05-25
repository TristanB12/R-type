/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** TcpController
*/

#include <algorithm>
#include "RtypeTcpController.hpp"
#include "RtypeTcpServer.hpp"

namespace rtype {
std::unordered_map<rtype::Protocol, TcpController::func_controller>
TcpController::mapControllers(void)
{
    return {
        { rtype::Protocol::GET_ROOMS, [this] { this->getAvailableRooms(); }},
        { rtype::Protocol::CREATE_ROOM, [this] { this->onCreateRoom(); }},
        { rtype::Protocol::JOIN_ROOM, [this] { this->onJoinRoom(); }},
        { rtype::Protocol::GET_ROOM_PLAYERS, [this] { this->onGetRoomPlayers(); }},
        { rtype::Protocol::LEAVE_ROOM, [this] { this->onLeaveRoom(); }},
        { rtype::Protocol::READY_UP, [this] { this->onReadyUp(); }},
        { rtype::Protocol::START_GAME, [this] { this->onStartGame(); }},
        { rtype::Protocol::END_GAME, [this] { this->onEndGame(); }}
    };
}

void TcpController::sendToRoom(
    std::shared_ptr<Room> room, Packet<rtype::Protocol> packet
)
{
    auto players = room->getPlayers();
    for (auto player : players) {
        packet.setClient(player);
        m_server.m_outQueue.push(packet);
    }
}

void TcpController::onDisconnect(std::shared_ptr<AClient> disconnectedClient)
{
    auto client = std::dynamic_pointer_cast<rtype::Client>(disconnectedClient);
    if (client == nullptr) {
        return;
    }
    auto clientRoom = m_server.m_roomManager.getRoomByID(client->getRoomID());
    if (clientRoom == nullptr) {
        return;
    }
    m_server.m_roomManager.removePlayerFromRoom(clientRoom->getRoomName(), client);
    Packet<rtype::Protocol> packet(rtype::Protocol::LEAVE_ROOM);
    packet << client->getID();
    this->sendToRoom(clientRoom, packet);
}

void TcpController::onCreateRoom(void)
{
    char roomName[MAX_ROOM_NAME_LEN + 1] = "";
    int roomId = -1;

    m_request >> roomName;
    if ((roomId = m_server.m_roomManager.createRoom(roomName)) == ROOM_MANAGER_FAILURE)
        std::cerr << "FAILED TO CREATE ROOM: " << roomName << std::endl;
    else {
        auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());
        m_server.m_roomManager.addPlayerToRoom(roomName, client);
        std::cout << "NEW ROOM CREATED: " << roomName << std::endl;
    }
    m_response << roomId;
    m_server.m_outQueue.push(m_response);
}

void TcpController::onJoinRoom(void)
{
    int roomID = -1;
    std::shared_ptr<Room> room = nullptr;

    m_request >> roomID;
    room = m_server.m_roomManager.getRoomByID(roomID);
    if (!room || room->isStarted() || room->getNbPlayer() == 4) {
        m_response << false;
        m_server.m_outQueue.push(m_response);
        return;
    }
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());

    // Notify other players of new join
    Packet<rtype::Protocol> packet(rtype::Protocol::PLAYER_JOIN_ROOM);
    packet << client->getID();
    this->sendToRoom(room, packet);

    m_server.m_roomManager.addPlayerToRoom(room->getRoomName(), client);
    m_response << true;
    m_server.m_outQueue.push(m_response);
}

void TcpController::onGetRoomPlayers(void) {
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());
    auto clientRoom = m_server.m_roomManager.getRoomByID(client->getRoomID());

    if (clientRoom) {
        for (auto player : clientRoom->getPlayers()) {
            m_response << player->getID() << player->isReady();
        }
    }
    m_server.m_outQueue.push(m_response);
}

void TcpController::onLeaveRoom(void) {
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());
    auto clientRoom = m_server.m_roomManager.getRoomByID(client->getRoomID());
    if (!clientRoom) {
        return;
    }
    client->toggleIsReady();
    m_server.m_roomManager.removePlayerFromRoom(clientRoom->getRoomName(), client);
    m_response << client->getID();
    this->sendToRoom(clientRoom, m_response);
}

void TcpController::onReadyUp(void)
{
    port_t clientUDPPort = 0;
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());

    if (client->getRoomID() == -1)
        return;
    auto clientRoom = m_server.m_roomManager.getRoomByID(client->getRoomID());
    if (clientRoom == nullptr) {
        return;
    }
    m_request >> clientUDPPort;
    client->setUdpPort(clientUDPPort);
    client->toggleIsReady();
    m_response << client->getID();
    this->sendToRoom(clientRoom, m_response);
    if (clientRoom->isRoomReady()) {
        onStartGame();
    }
}

void TcpController::onStartGame(void)
{
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());

    if (client->getRoomID() == -1) {
        return;
    }
    auto clientRoom = m_server.m_roomManager.getRoomByID(client->getRoomID());
    if (clientRoom == nullptr) {
        return;
    }
    clientRoom->startRoom();
    Packet<rtype::Protocol> packet(rtype::Protocol::START_GAME);
    packet << m_server.m_getUdpPort();
    this->sendToRoom(clientRoom, packet);
}

void TcpController::onEndGame(void)
{
    //TODO: immplement onEndGame
}

void TcpController::getAvailableRooms(void)
{
    size_t nbRooms = m_server.m_roomManager.getNbRooms();

    if (nbRooms == 0) {
        m_server.m_outQueue.push(m_response);
        return;
    }
    for (const std::shared_ptr<Room> &room : m_server.m_roomManager.getRooms()) {
        if (room->isRoomReady()) {
            continue;
        }
        char roomName[MAX_ROOM_NAME_LEN + 1] = "";
        std::strncpy(roomName, room->getRoomName().c_str(), MAX_ROOM_NAME_LEN);
        m_response << room->getId() << roomName << static_cast<uint8_t>((room->getNbPlayer()));
    }
    m_server.m_outQueue.push(m_response);
}


} // namespace rtype
