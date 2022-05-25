/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** AUdpSocket
*/

#pragma once

#include "ASocket.hpp"

template <typename T_Protocol>
class AUdpSocket : public ASocket<T_Protocol> {
public:
    virtual ~AUdpSocket(void) = default;

    // Bind to a local port
    virtual bool bind(port_t port) = 0;

    // Unbind the socket
    virtual void unbind(void) = 0;

    // Checks if the socket is currently bound
    virtual bool isBound(void) const = 0;

    // Send a packet to one peer
    virtual void send(const Packet<T_Protocol> &response,
        const std::string peerIpAddress,
        port_t peerPort
    ) = 0;

    void addPeer(const std::string peerIpAddress, port_t peerPort)
    {
        m_peers.push_back({ peerIpAddress, peerPort });
    }

protected:
    AUdpSocket(TSafeQueue<Packet<T_Protocol>> &queue) :
        ASocket<T_Protocol>(queue)
    {}

    void onIOError(void) override {
        ASocket<T_Protocol>::onIOError();
        this->unbind();
    }

    struct Peer {
        std::string ipAddress;
        port_t port;
    };

    std::vector<struct Peer> m_peers;
};