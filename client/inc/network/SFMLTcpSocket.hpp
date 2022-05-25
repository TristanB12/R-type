/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** SFMLTcpSocket
*/

#ifndef SFMLTCPSOCKET_HPP_
#define SFMLTCPSOCKET_HPP_

#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "ATcpSocket.hpp"

template <typename T_Protocol>
class SFMLTcpSocket : public ATcpSocket<T_Protocol> {
public:
    SFMLTcpSocket(TSafeQueue<Packet<T_Protocol>> &inQueue) :
        ATcpSocket<T_Protocol>(inQueue)
    {}

    // sf::TcpSocket automatically calls disconnect
    virtual ~SFMLTcpSocket(void) = default;

    bool connect(const std::string &ip_address, const port_t port) override
    {
        if (m_socket.connect(ip_address, port) != sf::Socket::Done) {
            return false;
        }
        this->m_packet.setIsFromDisconnect(false);
        return true;
    }

    void disconnect(void) override
    {
        m_socket.disconnect();
    }

    bool isConnected(void) const override
    {
        return m_socket.getRemotePort() != 0;
    }

    void send(const Packet<T_Protocol> &response) override
    {
        m_socket.send(response.getContent(), response.getTotalSize());
    }

    // This function needs to be called everytime we want to check
    // if we received a message.
    void startReceive(void) override
    {
        if (!this->isConnected()) {
            return;
        }
        m_socket.setBlocking(false);
        this->readHeader();
        m_socket.setBlocking(true);
    }

    ipv4_t getLocalAddress(void) const override
    {
        return sf::IpAddress::getLocalAddress().toInteger();
    }

    std::string getLocalAddressString(void) const override
    {
        return sf::IpAddress::getLocalAddress().toString();
    }

    port_t getLocalPort(void) const override
    {
        return m_socket.getLocalPort();
    }

    ipv4_t getRemoteAddress(void) const override
    {
        return m_socket.getRemoteAddress().toInteger();
    }

    std::string getRemoteAddressString(void) const override
    {
        return m_socket.getRemoteAddress().toString();
    }

private:
    void readHeader(void) override
    {
        if (!this->receive(&this->m_packet.getHeader(), this->m_packet.getHeaderSize())) {
            return;
        }
        if (this->m_packet.getExpectedBodySize() > 0) {
            this->readBody();
        } else {
            this->addToPacketQueue();
        }
    }

    void readBody(void) override
    {
        this->m_packet.resizeBody(this->m_packet.getExpectedBodySize());
        if (this->receive(this->m_packet.getBody().data(), this->m_packet.getBodySize())) {
            this->addToPacketQueue();
        }
    }

    bool receive(void *data, size_t size)
    {
        std::size_t bytesReceived = 0;
        sf::Socket::Status status = m_socket.receive(data, size, bytesReceived);

        if (status == sf::Socket::Status::Error || status == sf::Socket::Status::Disconnected) {
            this->onIOError();
            return false;
        }
        return status == sf::Socket::Status::Done;
    }

    sf::TcpSocket m_socket;
};

#endif /* !SFMLTCPSOCKET_HPP_ */
