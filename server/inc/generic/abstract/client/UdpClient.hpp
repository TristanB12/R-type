/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** AUdpClient
*/

#pragma once

#include "AClient.hpp"

class UdpClient : public AClient {
public:
    UdpClient(const std::string &address, port_t port) :
        m_address(address),
        m_port(port)
    {}
    virtual ~UdpClient(void) = default;

    virtual std::string getAddressString(void) const final
    {
        return m_address;
    }
    virtual port_t getPort(void) const final
    {
        return m_port;
    }

    virtual void setAddressString(const std::string &addressString) final
    {
        m_address = addressString;
    }

    virtual void setPort(port_t port) final
    {
        m_port = port;
    }

protected:
    std::string m_address;
    port_t m_port = 0;
};