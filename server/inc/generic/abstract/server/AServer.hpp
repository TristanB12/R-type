/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AServer
*/

#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include "AClient.hpp"
#include "AServerController.hpp"
#include "TSafeQueue.hpp"
#include "Packet.hpp"

using port_t = uint16_t;

template <typename T_Protocol>
class AServer {
public:
    virtual ~AServer(void) = default;

    virtual void run(void) final
    {
        m_controller->setup();
        this->onStart();
        while (1) {
            this->update();
        }
    }

    std::vector<std::shared_ptr<AClient>> &getClients(void)
    {
        return m_clients;
    }

protected:
    explicit AServer(const port_t port,
        std::shared_ptr<AServerController<T_Protocol>> controller
    ) : m_port(port),
        m_controller(controller)
    {}

    /* Non-overridable functions */
    virtual void update(void) final
    {
        m_inQueue.wait();
        while (!m_inQueue.isEmpty()) {
            this->processInput();
        }

        while (!m_outQueue.isEmpty()) {
            this->processOutput();
        }
    }

    virtual void addClient(std::shared_ptr<AClient> client)
    {
        this->onClientConnect(client);
        this->m_clients.push_back(client);
    }

    /* Pure virtual functions to override */
    virtual void processInput(void) = 0;
    virtual void processOutput(void) = 0;
    virtual void onStart(void) = 0;
    virtual void onStop(void) = 0;
    virtual void onClientConnect(std::shared_ptr<AClient> client) = 0;
    virtual void onClientDisconnect(std::shared_ptr<AClient> client) = 0;
    virtual void onRequestReceive(Packet<T_Protocol> &request) = 0;
    virtual void onResponseSend(Packet<T_Protocol> &response) = 0;

    port_t m_port;
    std::shared_ptr<AServerController<T_Protocol>> m_controller;
    TSafeQueue<Packet<T_Protocol>> m_inQueue;
    TSafeQueue<Packet<T_Protocol>> m_outQueue;
    std::vector<std::shared_ptr<AClient>> m_clients;
};
