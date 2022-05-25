/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** SFMLUdpSocket
*/

#pragma once

#include "AUdpSocket.hpp"

template <typename T_Protocol>
class SFMLUdpSocket : public AUdpSocket<T_Protocol> {
public:
    SFMLUdpSocket(TSafeQueue<Packet<T_Protocol>> &inQueue) :
        AUdpSocket<T_Protocol>(inQueue),
        m_buffer(512)
    {}

    virtual ~SFMLUdpSocket(void) = default;

    bool bind(port_t port) override
    {
        return m_socket.bind(port) == sf::Socket::Done;
    }

    void unbind(void) override
    {
        m_socket.unbind();
    }

    bool isBound(void) const
    {
        return m_socket.getLocalPort() != 0;
    }

    // Send a packet to every peer
    void send(const Packet<T_Protocol> &response) override
    {
        if (response.getTotalSize() > sf::UdpSocket::MaxDatagramSize) {
            return;
        }
        for (const auto &peer : this->m_peers) {
            m_socket.send(response.getContent(), response.getTotalSize(),
                sf::IpAddress(peer.ipAddress), peer.port
            );
        }
    }

    // Send a packet to one peer
    void send(const Packet<T_Protocol> &response, const std::string peerIpAddress,
        port_t peerPort) override
    {
        if (response.getTotalSize() > sf::UdpSocket::MaxDatagramSize) {
            return;
        }
        m_socket.send(response.getContent(), response.getTotalSize(),
            sf::IpAddress(peerIpAddress), peerPort
        );
    }

    // This function needs to be called everytime we want to check
    // if we received a message.
    void startReceive(void) override
    {
        if (!this->isBound()) {
            return;
        }
        m_socket.setBlocking(false);
        if (this->receive()) {
            ASocket<T_Protocol>::addToPacketQueue();
        }
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

private:
    bool receive(void)
    {
        std::size_t bytesReceived = 0;
        sf::IpAddress sender;
        unsigned short port;
        sf::Socket::Status status = m_socket.receive(
            m_buffer.data(), 512, bytesReceived, sender, port
        );

        if (status == sf::Socket::Status::Error) {
            ASocket<T_Protocol>::onIOError();
            return false;
        }
        if (bytesReceived > 0) {
            this->m_packet.setContent(m_buffer.data());
            m_buffer.clear();
        }
        return status == sf::Socket::Status::Done;
    }

    std::vector<char> m_buffer;
    sf::UdpSocket m_socket;
};