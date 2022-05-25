/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** RtypeUdpController
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "AServerController.hpp"
#include "Protocol.hpp"
#include "RtypeClient.hpp"
#include "UdpClient.hpp"

namespace rtype {
class UdpServer;

class UdpController : public AServerController<rtype::IngameProtocol> {
public:
    UdpController(rtype::UdpServer &server) :
        m_server(server)
    {}
    virtual ~UdpController(void) = default;

    void execute(const Packet<rtype::IngameProtocol> &request) override;

private:
    std::unordered_map<rtype::IngameProtocol, func_controller> mapControllers(void) override;

    std::shared_ptr<rtype::Client> resolveUdpClient(std::shared_ptr<AClient> client);

    void onMove(void);
    void onShoot(void);

    rtype::UdpServer &m_server;
};

} // namespace rtype
