/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** SFMLUdpClient
*/

#pragma once

#include "ASFMLClient.hpp"
#include "SFMLUdpSocket.hpp"

template <typename T_Protocol>
class SFMLUdpClient : public ASFMLClient<T_Protocol, SFMLUdpSocket<T_Protocol>>{
public:
    SFMLUdpClient(void) : ASFMLClient<T_Protocol, SFMLUdpSocket<T_Protocol>>() {}
    virtual ~SFMLUdpClient(void) = default;

    bool bind(port_t port)
    {
        return this->m_socket.bind(port) == sf::Socket::Done;
    }

    void unbind(void)
    {
        this->m_socket.unbind();
    }

    bool isBound(void) const
    {
        return this->m_socket.isBound();
    }

    void addPeer(const std::string &peerAddress, port_t peerPort)
    {
        this->m_socket.addPeer(peerAddress, peerPort);
    }

private:
    void onReceive(const Packet<T_Protocol> &packet) override
    {
        std::cout << "[UDP] Received from server --- " << std::endl
                << packet << std::endl;
    }

    void onSend(const Packet<T_Protocol> &packet) override
    {
        std::cout << "[UDP] Sending to server --- " << std::endl
                << packet << std::endl;
    }
};