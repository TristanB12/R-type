/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AServerController
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include "AClient.hpp"
#include "Packet.hpp"
#include "TSafeQueue.hpp"

template <typename T_Protocol>
class AServer;

/**
 * @brief Responsible for handling the logic of the server
 * regarding the protocol commands. The Controller takes in a request
 * and crafts a response.
 */
template <typename T_Protocol>
class AServerController {
public:
    virtual ~AServerController(void) = default;

    /**
     * This function needs to be called after instanciation of a controller.
     * It binds the member functions of its child classes with their class context ('this'),
     * which is not possible at instanciation.
     */
    void setup(void) {
        m_controllers = this->mapControllers();
    }

    virtual void execute(const Packet<T_Protocol> &request)
    {
        if (m_controllers.find(request.getId()) != m_controllers.end()) {
            m_request = request;
            m_response = request;
            m_response.clear();
            m_controllers[request.getId()]();
        } else {
            std::cerr << "Controller not found for request " << request << std::endl;
        }
    }

    virtual void onDisconnect(std::shared_ptr<AClient> client)
    {
        (void)client;
    }

protected:
    using func_controller = std::function<void (void)>;
    using controller_map = std::unordered_map<T_Protocol, func_controller>;

    virtual controller_map mapControllers(void) = 0;

    Packet<T_Protocol> m_request;
    Packet<T_Protocol> m_response;
    controller_map m_controllers;
};