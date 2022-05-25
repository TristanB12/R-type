/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** TitleState
*/

#include <iostream>
#include <cmath>
#include "StateManager.hpp"
#include "TitleState.hpp"
#include "Utils.hpp"

bool TitleState::handleEvent(const sf::Event &event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape) {
            m_context.stateManager.clear();
        } else {
            m_context.stateManager.navigate(States::ID::Menu);
        }
    } else if (event.type == sf::Event::JoystickMoved) {
        m_context.stateManager.navigate(States::ID::Menu);
    } else if (event.type == sf::Event::JoystickButtonPressed) {
        m_context.stateManager.navigate(States::ID::Menu);
    }
    return true;
}

bool TitleState::update(sf::Time dt)
{
    m_labelEffectTime += dt;

    if (m_labelEffectTime >= sf::seconds(0.5f))
    {
        m_showLabel = !m_showLabel;
        m_labelEffectTime = sf::Time::Zero;
    }
    std::dynamic_pointer_cast<gui::Label>(
        AMenuState::getComponent("MainScreenTitle")
    )->setColor(m_showLabel ? sf::Color::White : sf::Color::Transparent);
    return true;
}