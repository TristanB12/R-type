/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** ServerController
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "AServerController.hpp"
#include "Protocol.hpp"
#include "RoomsManager.hpp"

namespace rtype {
class TcpServer;

class TcpController : public AServerController<rtype::Protocol> {
public:
    TcpController(rtype::TcpServer &server) :
        m_server(server)
    {}
    virtual ~TcpController(void) = default;

    void onDisconnect(std::shared_ptr<AClient> client);

private:
    std::unordered_map<rtype::Protocol, func_controller> mapControllers(void) override;

    void sendToRoom(std::shared_ptr<Room> room, Packet<rtype::Protocol> packet);

    void onCreateRoom(void);
    void onJoinRoom(void);
    void onGetRoomPlayers(void);
    void getAvailableRooms(void);
    void onLeaveRoom(void);
    void onReadyUp(void);
    void onStartGame(void);
    void onEndGame(void);

    rtype::TcpServer &m_server;
};

} // namespace rtype
