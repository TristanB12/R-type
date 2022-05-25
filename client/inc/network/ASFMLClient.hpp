/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ASFMLClient
*/

#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include "ASocket.hpp"


template <typename T_Protocol, typename T_SFMLSocket>
class ASFMLClient {
static_assert(std::is_base_of<ASocket<T_Protocol>, T_SFMLSocket>::value, "SFML socket not recognized");
public:
    using protocol_callback_t = std::function<void (Packet<T_Protocol> &response)>;
    using disconnect_callback_t = std::function<void ()>;

    virtual ~ASFMLClient(void) = default;

    void send(const Packet<T_Protocol> &packet)
    {
        this->onSend(packet);
        m_socket.send(packet);
    }

    void send(T_Protocol id)
    {
        this->onSend(Packet<T_Protocol>(id));
        m_socket.send(id);
    }

    port_t getLocalPort(void) const
    {
        return m_socket.getLocalPort();
    }

    void handlePackets(void)
    {
        m_socket.startReceive();
        while (!m_queue.isEmpty()) {
            Packet<T_Protocol> packet = m_queue.pop();
            if (packet.isFromDisconnect()) {
                if (m_onDisconnect) {
                    m_onDisconnect();
                }
                return;
            }
            this->onReceive(packet);
            if (m_handlers.find(packet.getId()) != m_handlers.end()) {
                m_handlers[packet.getId()](packet);
            } else {
                std::cerr << "Handler not found for packet ID" << int(packet.getId()) << std::endl;
            }
        }
    }

    void setHandler(const T_Protocol protocol, protocol_callback_t func)
    {
        m_handlers[protocol] = func;
    }

    void setDisconnectCallback(disconnect_callback_t disconnectCallback)
    {
        m_onDisconnect = disconnectCallback;
    }

    void clearHandlers(void)
    {
        m_handlers.clear();
    }

protected:
    ASFMLClient(void) :
        m_socket(m_queue)
    {}

    virtual void onReceive(const Packet<T_Protocol> &packet)
    {
        std::cout << "--- Received from server --- " << std::endl
                << packet << std::endl;
    }

    virtual void onSend(const Packet<T_Protocol> &packet)
    {
        std::cout << "--- Sending to server --- " << std::endl
                << packet << std::endl;
    }

    T_SFMLSocket m_socket;

private:
    disconnect_callback_t m_onDisconnect;
    TSafeQueue<Packet<T_Protocol>> m_queue;
    std::unordered_map<T_Protocol, protocol_callback_t> m_handlers;
};
