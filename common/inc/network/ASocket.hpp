/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ATcpSocket
*/

#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include "Packet.hpp"
#include "TSafeQueue.hpp"

using ipv4_t = uint32_t;
using port_t = uint16_t;

/**
 * @brief Responsible for handling the IO between 2 network endpoints.
 */
template <typename T_Protocol>
class ASocket {
public:
    virtual ~ASocket(void) = default;

    // Makes a blocking write that sends the packet at once
    virtual void send(const Packet<T_Protocol> &packet) = 0;

    // Makes a blocking write that sends an ID only packet at once
    virtual void send(const T_Protocol &id)
    {
        this->send(Packet<T_Protocol>(id));
    }

    // Start non-blocking reads
    virtual void startReceive(void) = 0;

    // Return as a uint32_t the ip address of the local endpoint
    virtual ipv4_t getLocalAddress(void) const = 0;

    // Return as a string the ip address of the local endpoint
    virtual std::string getLocalAddressString(void) const = 0;

    // Return as a uint16_t the port of the local endpoint
    virtual port_t getLocalPort(void) const = 0;

    void setPacketClient(std::shared_ptr<AClient> client)
    {
        m_packet.setClient(client);
    }

protected:
    ASocket(TSafeQueue<Packet<T_Protocol>> &queue)
        : m_packetQueue(queue)
    {}

    virtual void onIOError(void) {
        /** A disconnection closes the socket but still sends the packet into the queue.
        * The server and the client will pick up the packet, and seeing that it signals
        * a disconnection, will remove the connection instead of executing the request.
        */
        m_packet.setIsFromDisconnect(true);
        this->addToPacketQueue();
    }

    void addToPacketQueue(void) {
        m_packetQueue.push(m_packet);
        m_packet.reset();
    }

    Packet<T_Protocol> m_packet;

private:
    TSafeQueue<Packet<T_Protocol>> &m_packetQueue;
};