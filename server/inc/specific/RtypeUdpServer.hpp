/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RtypeUdpServer
*/

#pragma once

#include "AsioUdpServer.hpp"
#include "RtypeUdpController.hpp"
#include "RoomsManager.hpp"

namespace rtype {
class UdpServer : public AsioUdpServer<rtype::IngameProtocol> {
public:
    UdpServer(
        port_t port,
        RoomsManager &roomManager,
        std::vector<std::shared_ptr<AClient>> &tcpClients
    ) :
        AsioUdpServer<rtype::IngameProtocol>(
            port,
            std::make_shared<rtype::UdpController>(*this)
        ),
        m_roomManager(roomManager),
        m_tcpClients(tcpClients)
    {}
    virtual ~UdpServer(void) = default;

private:
    RoomsManager &m_roomManager;
    std::vector<std::shared_ptr<AClient>> &m_tcpClients;
    friend class UdpController;
};
} // namespace rtype
