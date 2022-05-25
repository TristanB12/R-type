/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** GameState
*/

#pragma once

#include "AState.hpp"
#include "ecs/specific/RtypeCoordinator.hpp"
#include "EntityLoader.hpp"

class GameState : public AState {
public:
    GameState(SharedContext &context);
    virtual ~GameState(void);

    bool handleEvent(const sf::Event &event) override;
    bool update(sf::Time dt) override;
    void draw(void) override;

private:
    using handleEventFunc_t = void (GameState::*)(const sf::Event &event);
    void handleKeyPressedEvent(const sf::Event &event);
    void handleKeyReleasedEvent(const sf::Event &event);

    void handleJoystickMovedEvent();
    void handleJoystickButtonPressedEvent(const sf::Event &event);

    void beginAnimation(void);

    bool isOver(void);

    void onPlayerLeaveRoom(Packet<rtype::Protocol> &response);
    void onMove(Packet<rtype::IngameProtocol> &response);
    void onShoot(Packet<rtype::IngameProtocol> &response);

    std::unordered_map<sf::Event::EventType, handleEventFunc_t> m_eventHandlers;
    RtypeCoordinator m_coordinator;
    EntityLoader m_loader;
    EntitiesFlyWeight m_ennemies;
    EntitiesFlyWeight m_player_projectiles;
    sf::Clock m_clock;
    bool    m_animation = true;
};