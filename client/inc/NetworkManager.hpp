/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** NetworkManager
*/

#pragma once

#include "SFMLTcpClient.hpp"
#include "SFMLUdpClient.hpp"
#include "Protocol.hpp"

enum SocketType {
    TCP,
    UDP
};

class NetworkManager {
public:
    NetworkManager(void) = default;
    virtual ~NetworkManager(void) = default;

    // Connect to a server in TCP
    bool connect(const std::string &ipAddress, const port_t port)
    {
        return m_tcpClient.connect(ipAddress, port);
    }

    // Disconnect in TCP
    void disconnect(void)
    {
        return m_tcpClient.disconnect();
    }

    // Checks if the TCP connection is connected
    bool isConnected(void) const
    {
        return m_tcpClient.isConnected();
    }

    // Try to reconnect to the TCP server
    // Can only be called after a succesfull call to connect
    bool reconnect(void)
    {
        return m_tcpClient.reconnect();
    }

    // Bind to a local port in UDP
    bool bind(port_t port)
    {
        return m_udpClient.bind(port);
    }

    // Unbind in UDP
    void unbind(void)
    {
        return m_udpClient.unbind();
    }

    // Checks if we are bound in UDP
    bool isBound(void) const
    {
        return m_udpClient.isBound();
    }

    // Send a TCP packet
    void send(Packet<rtype::Protocol> &packet)
    {
        m_tcpClient.send(packet);
    }

    // Send a TCP packet only with an ID
    void send(const rtype::Protocol protocol)
    {
        m_tcpClient.send(protocol);
    }

    // Send a UDP packet
    void send(Packet<rtype::IngameProtocol> &packet)
    {
        m_udpClient.send(packet);
    }

    // Send a UDP packet only with an ID
    void send(const rtype::IngameProtocol ingameProtocol)
    {
        m_udpClient.send(ingameProtocol);
    }

    // Add a peer to send UDP packets to
    void addUdpPeer(const std::string &peerAddress, port_t peerPort)
    {
        m_udpClient.addPeer(peerAddress, peerPort);
    }

    // Handles all packets, trigerring their handlers if a message was received
    void handlePackets(void)
    {
        m_tcpClient.handlePackets();
        m_udpClient.handlePackets();
    }

    // Get the TCP or UDP local port
    port_t getLocalPort(SocketType socketType) const
    {
        if (socketType == SocketType::TCP) {
            return m_tcpClient.getLocalPort();
        } else if (socketType == SocketType::UDP) {
            return m_udpClient.getLocalPort();
        }
        return 0;
    }

    // Return the address of the TCP peer as a string
    std::string getTcpRemoteAddressString(void) const
    {
        return m_tcpClient.getRemoteAddressString();
    }

    // Set handler for TCP protocol
    void setHandler(const rtype::Protocol protocol,
        SFMLTcpClient<rtype::Protocol>::protocol_callback_t func)
    {
        m_tcpClient.setHandler(protocol, func);
    }

    // Set handler for UDP protocol
    void setHandler(const rtype::IngameProtocol protocol,
        SFMLUdpClient<rtype::IngameProtocol>::protocol_callback_t func)
    {
        m_udpClient.setHandler(protocol, func);
    }

    // Set handler for TCP disconnection
    void setDisconnectHandler(SFMLTcpClient<rtype::Protocol>::disconnect_callback_t callback)
    {
        m_tcpClient.setDisconnectCallback(callback);
    }

    // Clear the TCP or UDP handlers
    void clearHandlers(SocketType socketType)
    {
        if (socketType == SocketType::TCP) {
            m_tcpClient.clearHandlers();
        } else if (socketType == SocketType::UDP) {
            m_udpClient.clearHandlers();
        }
    }

private:
    SFMLTcpClient<rtype::Protocol> m_tcpClient;
    SFMLUdpClient<rtype::IngameProtocol> m_udpClient;
};
