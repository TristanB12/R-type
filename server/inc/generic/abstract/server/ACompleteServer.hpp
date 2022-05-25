/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ACompleteServer
*/

#pragma once

#include <thread>
#include "ATcpServer.hpp"
#include "AUdpServer.hpp"

// A server that handles TCP and UDP
template <typename TCP_Protocol, typename UDP_Protocol>
class ACompleteServer {
public:
    ACompleteServer(void) = default;
    ACompleteServer(
        std::shared_ptr<ATcpServer<TCP_Protocol>> tcpServer,
        std::shared_ptr<AUdpServer<UDP_Protocol>> udpServer
    ) : m_tcpServer(tcpServer),
        m_udpServer(udpServer)
    {}
    virtual ~ACompleteServer(void)
    {
        if (m_udpThread.joinable()) {
            m_udpThread.join();
        }
    }

    virtual void run(void) final
    {
        m_udpThread = std::thread([this] {
            m_udpServer->run();
        });
        m_tcpServer->run();
    }

protected:
    std::shared_ptr<ATcpServer<TCP_Protocol>> m_tcpServer = nullptr;
    std::shared_ptr<AUdpServer<UDP_Protocol>> m_udpServer = nullptr;

private:
    std::thread m_udpThread;
};
