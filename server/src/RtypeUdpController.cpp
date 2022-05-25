/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** UdpController
*/

#include <algorithm>
#include "RtypeUdpController.hpp"
#include "RtypeUdpServer.hpp"


namespace rtype {
std::unordered_map<rtype::IngameProtocol, UdpController::func_controller>
UdpController::mapControllers(void)
{
    return {
        { rtype::IngameProtocol::MOVE, [this] { this->onMove(); }},
        { rtype::IngameProtocol::SHOOT, [this] { this->onShoot(); }},
    };
}

void UdpController::execute(const Packet<rtype::IngameProtocol> &request)
{
    auto rtypeClient = this->resolveUdpClient(request.getClient());
    if (rtypeClient == nullptr) {
        return;
    }
    auto clientRoom = m_server.m_roomManager.getRoomByID(rtypeClient->getRoomID());
    if (clientRoom == nullptr) {
        return;
    }
    m_response = request;
    m_response << rtypeClient->getID();
    auto players = clientRoom->getPlayers();
    for (const auto &player : players) {
        auto udpClient = std::make_shared<UdpClient>(
            player->getAddressString(),
            player->getUdpPort());
        m_response.setClient(udpClient);
        m_server.m_outQueue.push(m_response);
    }
}

std::shared_ptr<rtype::Client> UdpController::resolveUdpClient(std::shared_ptr<AClient> client)
{
    auto udpClient = std::dynamic_pointer_cast<UdpClient>(client);
    if (udpClient == nullptr) {
        return nullptr;
    }
    auto it = std::find_if(
        m_server.m_tcpClients.begin(),
        m_server.m_tcpClients.end(),
        [udpClient] (const std::shared_ptr<AClient> &aClient) {
            auto rtypeClient = std::dynamic_pointer_cast<rtype::Client>(aClient);
            if (rtypeClient == nullptr) {
                return false;
            }
            return (
                rtypeClient->getAddressString() == udpClient->getAddressString()
                && rtypeClient->getUdpPort() == udpClient->getPort()
            );
    });
    return (it == m_server.m_tcpClients.end()) ? nullptr :
        std::dynamic_pointer_cast<rtype::Client>(*it);
}

void UdpController::onMove(void)
{
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());

    std::cout << "Client " << client->getID() << " requested to MOVE" << std::endl;
    m_server.m_outQueue.push(m_response);
}

void UdpController::onShoot(void)
{
    auto client = std::dynamic_pointer_cast<rtype::Client>(m_request.getClient());

    std::cout << "Client " << client->getID() << " requested to SHOOT" << std::endl;
    m_response << 42;
    m_server.m_outQueue.push(m_response);
}
} // namespace rtype