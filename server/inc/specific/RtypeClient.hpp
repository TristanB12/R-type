/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RtypeClient
*/

#pragma once

#include "AsioTcpClient.hpp"
#include "Protocol.hpp"

namespace rtype {
class Client : public AsioTcpClient<rtype::Protocol> {
public:
    Client(asio::ip::tcp::socket socket,
        TSafeQueue<Packet<rtype::Protocol>> &inQueue,
        int id
    ) : AsioTcpClient<rtype::Protocol>(std::move(socket), inQueue),
        m_id(id)
    {}
    virtual ~Client(void) = default;

    /*        getters         */
    inline bool isReady(void) {return m_isReady; };
    inline int getID(void) {return m_id; };
    inline int getRoomID(void) {return m_roomID; };
    inline port_t getUdpPort(void) { return m_udpPort; }

    /*        setters         */
    inline void setRoomID(int roomID) {m_roomID = roomID;}
    inline void setIsReady(bool isReady) {m_isReady = isReady;}
    inline void setUdpPort(port_t port) { m_udpPort = port; }

    /*        other methods         */
    inline void toggleIsReady(void) {m_isReady = !m_isReady;};
private:
    int m_id = -1;
    bool m_isReady = false;
    int m_roomID = -1;
    port_t m_udpPort = 0;
};
} // namespace rtype