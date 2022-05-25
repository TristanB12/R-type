/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ATcpSocket
*/

#pragma once

#include "ASocket.hpp"

template <typename T_Protocol>
class ATcpSocket : public ASocket<T_Protocol> {
public:
    virtual ~ATcpSocket(void) = default;

    // Makes a blocking connect, return true if connected, false otherwise
    virtual bool connect(const std::string &ip_address, const port_t port) = 0;

    // Makes a blocking disconnect
    virtual void disconnect(void) = 0;

    // Checks if the remote endpoint is still available
    virtual bool isConnected(void) const = 0;

    // Return as a uint32_t the ip address of the remote endpoint
    virtual ipv4_t getRemoteAddress(void) const = 0;

    // Return as a string the ip address of the remote endpoint
    virtual std::string getRemoteAddressString(void) const = 0;

protected:
    ATcpSocket(TSafeQueue<Packet<T_Protocol>> &queue) :
        ASocket<T_Protocol>(queue)
    {}

    void onIOError(void) override {
        ASocket<T_Protocol>::onIOError();
        this->disconnect();
    }

    virtual void readHeader(void) = 0;
    virtual void readBody(void) = 0;
};
