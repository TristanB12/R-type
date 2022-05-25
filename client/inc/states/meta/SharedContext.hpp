/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** SharedContext
*/

#pragma once

#include <optional>
#include "RessourceManager.hpp"
#include "AudioManager.hpp"
#include "NetworkManager.hpp"
#include "Protocol.hpp"
#include "Room.hpp"

namespace sf {
    class RenderWindow;
};

class StateManager;

struct SharedContext {
    SharedContext(sf::RenderWindow &window,
        RessourceManager &ressources,
        StateManager &stateManager,
        NetworkManager &networkManager,
        AudioManager &audioManager
    ) : window(window),
        ressources(ressources),
        stateManager(stateManager),
        network(networkManager),
        audio(audioManager)
    {}

    sf::RenderWindow &window;
    RessourceManager &ressources;
    StateManager &stateManager;
    NetworkManager &network;
    AudioManager &audio;
    std::optional<struct Room> room = std::nullopt;
};