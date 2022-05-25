/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** TCPClient
*/

#pragma once

#include "ASFMLClient.hpp"
#include "SFMLTcpSocket.hpp"

template <typename T_Protocol>
class SFMLTcpClient : public ASFMLClient<T_Protocol, SFMLTcpSocket<T_Protocol>> {
public:
    SFMLTcpClient(void) : ASFMLClient<T_Protocol, SFMLTcpSocket<T_Protocol>>(){}
    virtual ~SFMLTcpClient(void) = default;

    bool connect(const std::string &ipAddress, const port_t port)
    {
        if (!this->m_socket.connect(ipAddress, port)) {
            return false;
        }
        m_serverIpAddress = ipAddress;
        m_serverPort = port;
        return true;
    }

    void disconnect(void)
    {
        return this->m_socket.disconnect();
    }

    bool isConnected(void) const
    {
        return this->m_socket.isConnected();
    }

    // Can only be called after a successfull call to connect
    bool reconnect(void)
    {
        if (m_serverIpAddress.empty() || m_serverPort == 0) {
            return false;
        }
        return this->connect(m_serverIpAddress, m_serverPort);
    }

    std::string getRemoteAddressString(void) const
    {
        return this->m_socket.getRemoteAddressString();
    }

private:
    void onReceive(const Packet<T_Protocol> &packet) override
    {
        std::cout << "[TCP] Received from server --- " << std::endl
                << packet << std::endl;
    }

    void onSend(const Packet<T_Protocol> &packet) override
    {
        std::cout << "[TCP] Sending to server --- " << std::endl
                << packet << std::endl;
    }

    std::string m_serverIpAddress = "";
    port_t m_serverPort = 0;
};