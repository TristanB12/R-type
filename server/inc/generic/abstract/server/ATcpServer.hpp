/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ATcpServer
*/

#pragma once

#include "AServer.hpp"
#include "ATcpClient.hpp"

template <typename TCP_Protocol, typename UDP_Protocol>
class ACompleteServer;

template <typename T_Protocol>
class ATcpServer : public AServer<T_Protocol> {
public:
    virtual ~ATcpServer(void) = default;

protected:
    ATcpServer(const port_t port,
        std::shared_ptr<AServerController<T_Protocol>> controller
    ) : AServer<T_Protocol>(port, controller)
    {}

    void processInput(void) final
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

    void processOutput(void) final
    {
        Packet<T_Protocol> response = this->m_outQueue.pop();
        auto tcpClient = std::dynamic_pointer_cast<ATcpClient<T_Protocol>>(
            response.getClient()
        );

        if (tcpClient != nullptr && tcpClient->isConnected()) {
            this->onResponseSend(response);
            tcpClient->send(response);
        }
    }

    virtual void addClient(std::shared_ptr<AClient> client) final
    {
        AServer<T_Protocol>::addClient(client);
        auto tcpClient = std::dynamic_pointer_cast<ATcpClient<T_Protocol>>(
            client
        );

        if (tcpClient != nullptr) {
            tcpClient->startReceive();
        }
    }

    void onStart(void) override
    {
        std::cout << "[TCP] - Server listening on port " << this->m_port << "..." << std::endl;
    }

    void onStop(void) override
    {
        std::cout << "[TCP] - Server stopped." << std::endl;
    }

    void onClientConnect(std::shared_ptr<AClient> client) override
    {
        auto tcpClient = std::dynamic_pointer_cast<ATcpClient<T_Protocol>>(client);
        std::cout << "[TCP] - Client " << tcpClient->getAddressString() << " connected." << std::endl;
    }

    void onClientDisconnect(std::shared_ptr<AClient> client) override
    {
        // No address string can be retrieved in disconnect, since the remote_endpoint
        // is closed. You need to store it in the client class if you want to display it.
        (void)client;
        std::cout << "[TCP] - Client disconnected." << std::endl;
    }

    void onRequestReceive(Packet<T_Protocol> &request) override
    {
        auto tcpClient = std::dynamic_pointer_cast<ATcpClient<T_Protocol>>(
            request.getClient()
        );

        if (tcpClient != nullptr && tcpClient->isConnected()) {
            std::cout
                << "[TCP] - Received request from client "
                << tcpClient->getAddressString() << std::endl
                << request << std::endl;
        }
    }

    void onResponseSend(Packet<T_Protocol> &response) override
    {
        auto tcpClient = std::dynamic_pointer_cast<ATcpClient<T_Protocol>>(
            response.getClient()
        );

        if (tcpClient != nullptr && tcpClient->isConnected()) {
            std::cout
                << "[TCP] - Sending response to client "
                << tcpClient->getAddressString() << std::endl
                << response << std::endl;
        }
    }

private:
    template <typename TCP_Protocol, typename UDP_Protocol>
    friend class ACompleteServer;
};
