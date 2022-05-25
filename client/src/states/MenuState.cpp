/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** MenuState
*/

#include <iostream>
#include "MenuState.hpp"
#include "StateManager.hpp"
#include "Utils.hpp"
#include "Button.hpp"
#include "StackPanel.hpp"

MenuState::MenuState(SharedContext &context) :
    AMenuState(context, "Menu.conf")
{
    m_context.room = std::nullopt;
    auto stackPanel = std::dynamic_pointer_cast<gui::StackPanel>(
        AMenuState::getComponent("ButtonStackPanel")
    );

    std::dynamic_pointer_cast<gui::Button>(
        stackPanel->getComponent("CreateRoomButton")
    )->setCallback([this] {
        m_context.stateManager.navigate(States::ID::CreateRoom);
    });

    std::dynamic_pointer_cast<gui::Button>(
        stackPanel->getComponent("JoinRoomButton")
    )->setCallback([this] {
        m_context.stateManager.navigate(States::ID::JoinRoom);
    });

    std::dynamic_pointer_cast<gui::Button>(
        stackPanel->getComponent("ControlsButton")
    )->setCallback([this] {
        m_context.stateManager.navigate(States::ID::Controls);
    });

    std::dynamic_pointer_cast<gui::Button>(
        stackPanel->getComponent("CreditsButton")
    )->setCallback([this] {
        m_context.stateManager.navigate(States::ID::Credits);
    });

    std::dynamic_pointer_cast<gui::Button>(
        stackPanel->getComponent("QuitButton")
    )->setCallback([this] {
        m_context.stateManager.clear();
    });
}