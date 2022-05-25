/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RtypeServer
*/

#pragma once

#include <memory>
#include "ACompleteServer.hpp"
#include "RtypeTcpServer.hpp"
#include "RtypeUdpServer.hpp"
#include "RoomsManager.hpp"

namespace rtype {
class Server : public ACompleteServer<rtype::Protocol, rtype::IngameProtocol> {
public:
    Server(port_t tcpPort, port_t udpPort = 0)
    {
        this->m_tcpServer = std::make_shared<rtype::TcpServer>(
            tcpPort,
            m_roomManager,
            [this] { return this->m_udpServer->getLocalPort(); }
        );
        this->m_udpServer = std::make_shared<rtype::UdpServer>(
            udpPort,
            m_roomManager,
            this->m_tcpServer->getClients()
        );
    }
    virtual ~Server(void) = default;

private:
    RoomsManager m_roomManager;
};
} // namespace rtype
