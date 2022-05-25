/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** RoomState
*/

#include "RoomState.hpp"
#include "StateManager.hpp"
#include "gui.hpp"
#include "Utils.hpp"
#include "Room.hpp"

RoomState::RoomState(SharedContext &context) :
    AMenuState(context,"RoomState.conf"),
    m_playerList(std::make_shared<gui::PlayerList>())
{
    if (m_context.room == std::nullopt) {
        std::cerr << "Invalid room" << std::endl;
        return;
    }
    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("GoBackButton")
    )->setCallback([this] () {
        m_context.network.send(rtype::Protocol::LEAVE_ROOM);
        m_context.stateManager.navigate(States::ID::Menu);
    });

    auto roomNameLabel = std::make_shared<gui::Label>(
        std::string("Room : ") + m_context.room.value().name,
        m_context.ressources.getDefaultFont()
    );
    roomNameLabel->setHorizontalAlignement(gui::HorizontalAlignement::CENTER);
    roomNameLabel->setMargin({ 0, 75, 0, 0});

    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("ReadyUpButon")
    )->setCallback([this] () {
        if (!m_context.network.isBound()) {
            m_context.network.bind(sf::Socket::AnyPort);
        }
        Packet<rtype::Protocol> packet(rtype::Protocol::READY_UP);
        packet << m_context.network.getLocalPort(SocketType::UDP);
        m_context.network.send(packet);
    });

    m_playerList->setMargin({ 50, 200, 0, 0});
    AMenuState::addGUIComponent(roomNameLabel);
    AMenuState::addGUIComponent(m_playerList);
    SET_TCP_HANDLER(GET_ROOM_PLAYERS, onGetRoomPlayers);
    SET_TCP_HANDLER(PLAYER_JOIN_ROOM, onPlayerJoinRoom);
    SET_TCP_HANDLER(LEAVE_ROOM, onPlayerLeaveRoom);
    SET_TCP_HANDLER(READY_UP, onPlayerReadyUp);
    SET_TCP_HANDLER(START_GAME, onStartGame);
    m_context.network.send(rtype::Protocol::GET_ROOM_PLAYERS);
}

void RoomState::onGetRoomPlayers(Packet<rtype::Protocol> &response)
{
    std::vector<gui::PlayerItem::Ptr> players;
    sf::Vector2u playerItemSize(
        calcPercentage(80, static_cast<int>(m_context.window.getSize().x)),
        75
    );

    while (response.getBodySize() > 0) {
        struct Player player;
        bool isReady = false;

        response >> isReady >> player.id;
        auto playerItem = std::make_shared<gui::PlayerItem>(
            player,
            isReady,
            m_context.ressources.getTexture("r-typesheet42"),
            m_context.ressources.getDefaultFont(),
            playerItemSize
        );
        players.push_back(playerItem);
    }
    int i = 0;
    // Add in reverse since we read the players in reverse
    for (auto it = players.rbegin() ; it != players.rend() ; it++, i++) {
        (*it)->setColor(static_cast<Player::Color>(i));
        m_playerList->addPlayer(*it);
    }
}

void RoomState::onPlayerJoinRoom(Packet<rtype::Protocol> &response)
{
    sf::Vector2u playerItemSize(
        calcPercentage(80, static_cast<int>(m_context.window.getSize().x)),
        75
    );
    struct Player player;

    response >> player.id;
    player.color = static_cast<Player::Color>(m_playerList->getNbPlayers());
    auto playerItem = std::make_shared<gui::PlayerItem>(
        player,
        false,
        m_context.ressources.getTexture("r-typesheet42"),
        m_context.ressources.getDefaultFont(),
        playerItemSize
    );
    m_playerList->addPlayer(playerItem);
}

void RoomState::onPlayerLeaveRoom(Packet<rtype::Protocol> &response)
{
    int32_t playerID = 0;

    response >> playerID;
    m_playerList->removePlayer(playerID);
}

void RoomState::onPlayerReadyUp(Packet<rtype::Protocol> &response)
{
    int32_t playerID = 0;

    response >> playerID;
    m_playerList->togglePlayerReady(playerID);
}

void RoomState::onStartGame(Packet<rtype::Protocol> &response)
{
    port_t serverPort = 0;

    response >> serverPort;
    m_context.network.addUdpPeer(
        m_context.network.getTcpRemoteAddressString(), serverPort
    );
    for (const struct Player &player : m_playerList->getPlayers()) {
        m_context.room.value().players.push_back(player);
    }
    m_context.audio.stopMusic();
    m_context.stateManager.navigate(States::ID::Game);
}