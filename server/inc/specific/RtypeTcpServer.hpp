/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RtypeTcpServer
*/

#pragma once

#include "AsioTcpServer.hpp"
#include "RtypeTcpController.hpp"
#include "RoomsManager.hpp"

namespace rtype {
class TcpServer : public AsioTcpServer<rtype::Protocol> {
public:
    TcpServer(port_t port, RoomsManager &roomManager, std::function<port_t ()> getUdpPort) :
        AsioTcpServer<rtype::Protocol>(
            port,
            std::make_shared<rtype::TcpController>(*this)
        ),
        m_roomManager(roomManager),
        m_getUdpPort(std::move(getUdpPort))
    {}
    virtual ~TcpServer(void) = default;

private:
    std::shared_ptr<AsioTcpClient<rtype::Protocol>>
    createNewClient(asio::ip::tcp::socket socket) override
    {
        return std::make_shared<rtype::Client>(
            std::move(socket), this->m_inQueue, this->m_clientID++
        );
    };

    void onClientConnect(std::shared_ptr<AClient> client) override
    {
        auto rtypeClient = std::dynamic_pointer_cast<rtype::Client>(client);
        std::cout << "Client " << rtypeClient->getID() << " connected." << std::endl;
    }

    void onClientDisconnect(std::shared_ptr<AClient> client) override
    {
        auto rtypeClient = std::dynamic_pointer_cast<rtype::Client>(client);
        std::cout << "Client " << rtypeClient->getID() << " disconnected." << std::endl;
    }

    unsigned int m_clientID = 42;
    RoomsManager &m_roomManager;
    std::function<port_t ()> m_getUdpPort;
    friend class TcpController;
};
} // namespace rtype
