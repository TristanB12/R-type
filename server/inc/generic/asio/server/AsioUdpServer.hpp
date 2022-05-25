/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioServer
*/

#pragma once

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE 1

#include <asio.hpp>
#include <thread>
#include "AUdpServer.hpp"
#include "AsioUdpSocket.hpp"

template <typename T_Protocol>
class AsioUdpServer : public AUdpServer<T_Protocol> {
public:
    AsioUdpServer(port_t port,
        std::shared_ptr<AServerController<T_Protocol>> controller
    ) : AUdpServer<T_Protocol>(port, controller)
    {
        this->m_socket = std::make_shared<AsioUdpSocket<T_Protocol>>(
            m_context, port, this->m_inQueue
        );
    }

    virtual ~AsioUdpServer(void)
    {
        m_context.stop();

        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

protected:
    void onStart(void) override
    {
        m_thread = std::thread([this] {
            m_context.run();
        });
        AUdpServer<T_Protocol>::onStart();
    }

private:
    asio::io_context m_context;
    std::thread m_thread;
};
