/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ConnectionLostState
*/

#include "ConnectionLostState.hpp"
#include "Button.hpp"
#include "StateManager.hpp"

ConnectionLostState::ConnectionLostState(SharedContext &context) :
    AMenuState(context, "ConnectionLost.conf")
{
    m_blurRectangle.setSize(sf::Vector2f(m_context.window.getSize()));
    m_blurRectangle.setFillColor(sf::Color(127, 127, 127, 120));
    m_blurRectangle.setOutlineColor(sf::Color(127, 127, 127));
    m_blurRectangle.setOutlineThickness(5.0f);
    std::dynamic_pointer_cast<gui::Button>(
        std::dynamic_pointer_cast<gui::StackPanel>(
            AMenuState::getComponent("ReconnectStackPanel")
        )->getComponent("ReconnectButton")
    )->setCallback([this]
    {
        if (m_context.network.reconnect()) {
            m_context.stateManager.popCurrentState();
        }
    });
}

void ConnectionLostState::draw(void)
{
    m_context.window.draw(m_blurRectangle);
    AMenuState::draw();
}