/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioClient
*/

#pragma once

#include "ATcpClient.hpp"
#include "AsioTcpSocket.hpp"

// Simply an AClient with an AsioTcpSocket
template <typename T_Protocol>
class AsioTcpClient : public ATcpClient<T_Protocol> {
public:
    AsioTcpClient(
        asio::ip::tcp::socket socket,
        TSafeQueue<Packet<T_Protocol>> &inQueue
    ) : ATcpClient<T_Protocol>(
            std::make_shared<AsioTcpSocket<T_Protocol>>(std::move(socket), inQueue)
        )
    {}
    virtual ~AsioTcpClient(void) = default;
};

