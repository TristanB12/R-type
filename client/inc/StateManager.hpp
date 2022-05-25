/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** StateManager
*/

#pragma once

#include "StateStack.hpp"
#include "ParallaxState.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "CreateRoomState.hpp"
#include "JoinRoomState.hpp"
#include "ControlsState.hpp"
#include "CreditsState.hpp"
#include "RoomState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "ConnectionLostState.hpp"
#include "GameLostState.hpp"

class StateManager {
public:
    StateManager(
        sf::RenderWindow &window,
        RessourceManager &ressources,
        NetworkManager &networkManager,
        AudioManager &audioManager
    ) : m_stateStack(SharedContext(
            window, ressources, *this, networkManager, audioManager
        ))
    {
        this->registerStates();
    }
    virtual ~StateManager(void) = default;

    bool isEmpty(void) const
    {
        return m_stateStack.isEmpty();
    }

    void handleEvent(const sf::Event &event)
    {
        m_stateStack.handleEvent(event);
    }

    void update(sf::Time dt)
    {
        m_stateStack.update(dt);
    }

    void draw(void)
    {
        m_stateStack.draw();
    }

    void navigate(States::ID stateID, bool popCurrentState = true)
    {
        if (popCurrentState) {
            this->popCurrentState();
        }
        m_stateStack.pushState(stateID);
    }

    void popCurrentState(void)
    {
        m_stateStack.popState();
    }

    void clear(void)
    {
        m_stateStack.clearStates();
    }

    States::ID getCurrentStateID(void) const
    {
        return m_stateStack.getCurrentStateID();
    }

private:
    void registerStates(void)
    {
        m_stateStack.registerState<ParallaxState>(States::ID::Parallax);
        m_stateStack.registerState<TitleState>(States::ID::Title);
        m_stateStack.registerState<MenuState>(States::ID::Menu);
        m_stateStack.registerState<CreateRoomState>(States::ID::CreateRoom);
        m_stateStack.registerState<JoinRoomState>(States::ID::JoinRoom);
        m_stateStack.registerState<ControlsState>(States::ID::Controls);
        m_stateStack.registerState<CreditsState>(States::ID::Credits);
        m_stateStack.registerState<RoomState>(States::ID::Room);
        m_stateStack.registerState<GameState>(States::ID::Game);
        m_stateStack.registerState<PauseState>(States::ID::Pause);
        m_stateStack.registerState<ConnectionLostState>(States::ID::ConnectionLost);
        //m_stateStack.registerState<GameLostState>(States::ID::GameLost);
    }

    StateStack m_stateStack;
};