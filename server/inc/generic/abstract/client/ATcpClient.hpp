/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ATcpClient
*/

#pragma once

#include "AClient.hpp"
#include "ATcpSocket.hpp"

template <typename T_Protocol>
class ATcpClient : public AClient {
public:
    virtual ~ATcpClient(void) = default;

    bool isConnected(void) const
    {
        return m_tcpSocket->isConnected();
    }

    void startReceive(void)
    {
        m_tcpSocket->setPacketClient(this->shared_from_this());
        m_tcpSocket->startReceive();
    }

    void send(const Packet<T_Protocol> &packet)
    {
        m_tcpSocket->send(packet);
    }

    ipv4_t getAddress(void) const
    {
        return m_tcpSocket->getRemoteAddress();
    }

    std::string getAddressString(void) const
    {
        return m_tcpSocket->getRemoteAddressString();
    }

protected:
    ATcpClient(std::shared_ptr<ATcpSocket<T_Protocol>> tcpSocket) :
        m_tcpSocket(tcpSocket)
    {}

    std::shared_ptr<ATcpSocket<T_Protocol>> m_tcpSocket = nullptr;
};