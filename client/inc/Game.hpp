/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Game
*/

#pragma once

#include <memory>
#include "RessourceManager.hpp"
#include "StateManager.hpp"
#include "AudioManager.hpp"
#include "NetworkManager.hpp"
#include "Protocol.hpp"

namespace rtype {
class Game {
public:
    Game(void);
    virtual ~Game(void) = default;

    bool run(const std::string &serverIpAddress, port_t serverPort);

private:
    void processInput(void);
    void update(const sf::Time &dt);
    void render(void);

    sf::RenderWindow m_window;
    RessourceManager m_ressources;
    NetworkManager m_network;
    AudioManager m_audioManager;
    StateManager m_stateManager;
};
} // namespace rtype
