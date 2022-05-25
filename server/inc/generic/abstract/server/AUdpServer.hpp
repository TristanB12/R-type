/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** AUdpServer
*/

#pragma once

#include "AServer.hpp"
#include "UdpClient.hpp"
#include "AUdpSocket.hpp"

template <typename TCP_Protocol, typename UDP_Protocol>
class ACompleteServer;

template <typename T_Protocol>
class AUdpServer : public AServer<T_Protocol> {
public:
    virtual ~AUdpServer(void) = default;

    virtual port_t getLocalPort(void) const final
    {
        return m_socket->getLocalPort();
    }

protected:
    AUdpServer(port_t port,
        std::shared_ptr<AServerController<T_Protocol>> controller
    ) : AServer<T_Protocol>(port, controller)
    {}

    void processInput(void) override
    {
        Packet<T_Protocol> request = this->m_inQueue.pop();

        if (request.isFromDisconnect()) {
            this->onClientDisconnect(request.getClient());
            this->m_controller->onDisconnect(request.getClient());
            this->m_clients.erase(
                std::remove(this->m_clients.begin(), this->m_clients.end(), request.getClient()),
                this->m_clients.end()
            );
        } else {
            this->onRequestReceive(request);
            this->m_controller->execute(request);
        }
    }

    void processOutput(void) override
    {
        Packet<T_Protocol> response = this->m_outQueue.pop();
        auto udpClient = std::dynamic_pointer_cast<UdpClient>(
            response.getClient()
        );

        if (udpClient != nullptr) {
            this->onResponseSend(response);
            this->m_socket->send(response, udpClient->getAddressString(), udpClient->getPort());
        }
    }

    void onStart(void) override
    {
        this->m_socket->startReceive();
        std::cout << "[UDP] - Server listening on port " << this->m_port << "..." << std::endl;
    }

    void onStop(void) override
    {
        std::cout << "[UDP] - Server stopped." << std::endl;
    }

    void onClientConnect(std::shared_ptr<AClient> client) override
    {
        auto udpClient = std::dynamic_pointer_cast<UdpClient>(client);
        std::cout << "[UDP] - Client " << udpClient->getAddressString()
                << ":" << udpClient->getPort() << " added." << std::endl;
    }

    void onClientDisconnect(std::shared_ptr<AClient> client) override
    {
        auto udpClient = std::dynamic_pointer_cast<UdpClient>(client);
        std::cout << "[UDP] - Client " << udpClient->getAddressString()
                << ":" << udpClient->getPort() << " removed." << std::endl;
    }

    void onRequestReceive(Packet<T_Protocol> &request) override
    {
        auto udpClient = std::dynamic_pointer_cast<UdpClient>(
            request.getClient()
        );

        if (udpClient != nullptr) {
            std::cout
                << "[UDP] - Received request from client "
                << udpClient->getAddressString() << std::endl
                << request << std::endl;
        }
    }

    void onResponseSend(Packet<T_Protocol> &response) override
    {
        auto udpClient = std::dynamic_pointer_cast<UdpClient>(
            response.getClient()
        );

        if (udpClient != nullptr) {
            std::cout
                << "[UDP] - Sending response to client "
                << udpClient->getAddressString() << std::endl
                << response << std::endl;
        }
    }

protected:
    std::shared_ptr<AUdpSocket<T_Protocol>> m_socket = nullptr;

private:
    template <typename TCP_Protocol, typename UDP_Protocol>
    friend class ACompleteServer;
};
