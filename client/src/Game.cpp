/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Game
*/

#include <iostream>
#include "Game.hpp"
#include "TitleState.hpp"

namespace rtype {
Game::Game(void) :
    m_window(sf::VideoMode(1280, 720), "RType", sf::Style::Close),
    m_ressources("PressStart2P"),
    m_audioManager(m_ressources),
    m_stateManager(m_window, m_ressources, m_network, m_audioManager)
{
    sf::Image icon;

    if (icon.loadFromFile("./assets/textures/r-type_icon.png")) {
        m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    m_window.setFramerateLimit(60);
    m_network.setDisconnectHandler([this] {
        m_stateManager.navigate(States::ID::Menu);
        if (m_stateManager.getCurrentStateID() != States::ID::ConnectionLost) {
            m_stateManager.navigate(States::ID::ConnectionLost, false);
        }
    });
    m_stateManager.navigate(States::ID::Parallax, false);
    m_stateManager.navigate(States::ID::Title, false);
}

bool Game::run(const std::string &serverIpAddress, port_t serverPort)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

    if (!m_network.connect(serverIpAddress, serverPort)) {
        std::cerr << "Couldn't connect to server" << std::endl;
        return false;
    }
    while (m_window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            this->processInput();
            this->update(timePerFrame);
            // Check inside this loop, because stack might be empty before update() call
            if (m_stateManager.isEmpty()) {
                m_window.close();
            }
        }
        this->render();
    }
    return true;
}

void Game::processInput(void)
{
    sf::Event event;
    m_network.handlePackets();
    while (m_window.pollEvent(event)) {
        m_stateManager.handleEvent(event);
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void Game::update(const sf::Time &dt)
{
    m_stateManager.update(dt);
}

void Game::render(void)
{
    m_window.clear();
    m_stateManager.draw();
    m_window.display();
}
} // namespace rtype
