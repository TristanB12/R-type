/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** AsioUdpSocket
*/

#pragma once

#ifdef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE 1

#include <asio.hpp>
#include <array>
#include "AUdpSocket.hpp"
#include "UdpClient.hpp"

template <typename T_Protocol>
class AsioUdpSocket : public AUdpSocket<T_Protocol> {
public:
    AsioUdpSocket(
        asio::io_service &context,
        TSafeQueue<Packet<T_Protocol>> &queue
    ) : AUdpSocket<T_Protocol>(queue),
        m_socket(context),
        m_buffer(512)
    {}
    AsioUdpSocket(
        asio::io_service &context,
        port_t port,
        TSafeQueue<Packet<T_Protocol>> &queue
    ) : AUdpSocket<T_Protocol>(queue),
        m_socket(context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
        m_buffer(512)
    {}

    virtual ~AsioUdpSocket(void) = default;

    bool bind(port_t port) override
    {
        asio::error_code err;

        if (!m_socket.is_open()) {
            m_socket.open(asio::ip::udp::v4(), err);
            if (err) {
                std::cerr << err.message() << std::endl;
                return false;
            }
        }
        m_socket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), port), err);
        if (err) {
            std::cerr << err.message() << std::endl;
            return false;
        }
        return true;
    }

    void unbind(void) override
    {
        if (this->isBound()) {
            m_socket.close();
        }
    }

    bool isBound(void) const override
    {
        return m_socket.is_open();
    }

    void startReceive(void) override
    {
        m_socket.async_receive_from(
            asio::buffer(m_buffer, 512),
            m_senderEndpoint,
            [this] (const std::error_code &err, const std::size_t &length) {
                (void)length;
                if (err && err != asio::error::message_size) {
                    this->onIOError();
                    return;
                }
                this->m_packet.setClient(std::make_shared<UdpClient>(
                    m_senderEndpoint.address().to_string(), m_senderEndpoint.port()
                ));
                this->m_packet.setContent(m_buffer.data());
                this->addToPacketQueue();
                this->startReceive();
            }
        );
    }

    void send(const Packet<T_Protocol> &packet) override
    {
        for (const auto &peer : this->m_peers) {
            this->send(packet, peer.ipAddress, peer.port);
        }
    }

    void send(const Packet<T_Protocol> &response,
        const std::string peerIpAddress,
        port_t peerPort
    ) override
    {
        auto remote = asio::ip::udp::endpoint(
            asio::ip::address::from_string(peerIpAddress), peerPort
        );

        m_socket.async_send_to(asio::buffer(response.getContent(), 512), remote,
            [this] (const std::error_code &err, std::size_t size) {
                (void)size;
                if (err) {
                    this->onIOError();
                }
        });
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

private:
    asio::ip::udp::socket m_socket;
    std::vector<char> m_buffer;
    asio::ip::udp::endpoint m_senderEndpoint;
};
