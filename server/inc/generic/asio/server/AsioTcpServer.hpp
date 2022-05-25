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
#include "ATcpServer.hpp"
#include "AsioTcpClient.hpp"
#include "AsioUdpSocket.hpp"

template <typename T_Protocol>
class AsioTcpServer : public ATcpServer<T_Protocol> {
public:
    AsioTcpServer(const port_t port,
        std::shared_ptr<AServerController<T_Protocol>> controller
    ) : ATcpServer<T_Protocol>(port, controller),
        m_acceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    {}
    virtual ~AsioTcpServer(void)
    {
        m_context.stop();

        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

protected:
    virtual std::shared_ptr<AsioTcpClient<T_Protocol>>
    createNewClient(asio::ip::tcp::socket socket)
    {
        return std::make_shared<AsioTcpClient<T_Protocol>>(
            std::move(socket), this->m_inQueue
        );
    };

private:
    void onStart(void) override
    {
        this->startAccepts();
        m_thread = std::thread([this] {
            m_context.run();
        });
        ATcpServer<T_Protocol>::onStart();
    }

    virtual void startAccepts(void) final
    {
        m_acceptor.async_accept([this] (const std::error_code &err, asio::ip::tcp::socket socket) {
            if (err) {
                std::cerr << "Couldn't accept connection: " << err.message() << std::endl;
            } else {
                ATcpServer<T_Protocol>::addClient(this->createNewClient(std::move(socket)));
            }
            this->startAccepts();
        });
    }

    asio::io_context m_context;
    asio::ip::tcp::acceptor m_acceptor;
    std::thread m_thread;
};
