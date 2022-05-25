/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTcpSocket
*/

#pragma once

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE 1

#include <asio.hpp>
#include <array>
#include "ATcpSocket.hpp"

template <typename T_Protocol>
class AsioTcpSocket : public ATcpSocket<T_Protocol> {
public:
    AsioTcpSocket(
        asio::ip::tcp::socket socket,
        TSafeQueue<Packet<T_Protocol>> &queue
    ) :
        ATcpSocket<T_Protocol>(queue),
        m_socket(std::move(socket))
    {}
    virtual ~AsioTcpSocket(void)
    {
        this->disconnect();
    }

    bool connect(const std::string &ip_address, const port_t port) override
    {
        asio::ip::address address = asio::ip::make_address(ip_address);
        asio::ip::tcp::endpoint endpoint(address, port);
        asio::error_code err;

        m_socket.connect(endpoint, err);
        if (err) {
            return false;
        }
        return true;
    }

    void disconnect(void) override
    {
        if (this->isConnected()) {
            m_socket.close();
        }
    }

    bool isConnected(void) const override
    {
        return m_socket.is_open();
    }

    void send(const Packet<T_Protocol> &response) override
    {
        const auto sequence = this->const_sequence(
            asio::buffer(&response.getHeader(), response.getHeaderSize()),
            asio::buffer(response.getBody(), response.getBodySize())
        );

        asio::async_write(m_socket, sequence,
            [this] (const std::error_code &err, const std::size_t &length) {
                (void)length;
                if (err) {
                    this->onIOError();
                }
            }
        );
    }

    void startReceive(void) override
    {
        this->readHeader();
    }

    ipv4_t getLocalAddress(void) const override
    {
        asio::error_code err;
        ipv4_t localAddress = m_socket.local_endpoint(err).address().to_v4().to_uint();

        return err ? 0 : localAddress;
    }

    std::string getLocalAddressString(void) const override
    {
        asio::error_code err;
        std::string localAddressString = m_socket.local_endpoint(err).address().to_string();

        return err ? "" : localAddressString;
    }

    port_t getLocalPort(void) const override
    {
        asio::error_code err;
        port_t localPort = m_socket.local_endpoint(err).port();

        return err ? 0 : localPort;
    }

    ipv4_t getRemoteAddress(void) const override
    {
        asio::error_code err;
        ipv4_t remoteAddress = m_socket.remote_endpoint(err).address().to_v4().to_uint();

        return err ? 0 : remoteAddress;
    }

    std::string getRemoteAddressString(void) const override
    {
        asio::error_code err;
        std::string remoteAddressString = m_socket.remote_endpoint(err).address().to_string();

        return err ? "" : remoteAddressString;
    }

private:
    void readHeader(void) override
    {
        asio::async_read(m_socket, asio::buffer(&this->m_packet.getHeader(), this->m_packet.getHeaderSize()),
            [this] (const std::error_code &err, const std::size_t &length) {
                (void)length;
                if (err) {
                    this->onIOError();
                } else {
                    if (this->m_packet.getExpectedBodySize() > 0) {
                        this->readBody();
                    } else {
                        this->addToPacketQueue();
                        this->readHeader();
                    }
                }
            }
        );
    }

    void readBody(void) override
    {
        this->m_packet.resizeBody(this->m_packet.getExpectedBodySize());
        asio::async_read(m_socket, asio::buffer(this->m_packet.getBody().data(), this->m_packet.getBodySize()),
            [this] (const std::error_code &err, const std::size_t &length) {
                (void)length;
                if (err) {
                    this->onIOError();
                } else {
                    this->addToPacketQueue();
                    this->readHeader();
                }
            }
        );
    }

    template <typename... Args>
    auto const_sequence(Args&&... args)
    {
        return std::array<asio::const_buffer, sizeof...(Args)>{asio::buffer(args)...};
    }

    asio::ip::tcp::socket m_socket;
};