/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** PauseState
*/

#include "PauseState.hpp"
#include "Button.hpp"
#include "StateManager.hpp"
#include "Utils.hpp"

PauseState::PauseState(SharedContext &context) :
    AMenuState(context, "Pause.conf")
{
    sf::Vector2f windowSize(m_context.window.getSize());
    m_blurRectangle.setSize(sf::Vector2f(
        windowSize.x, calcPercentage(20.0f, windowSize.y)
    ));
    m_blurRectangle.setPosition(
        0, calcPercentage(40.0f, windowSize.y)
    );
    m_blurRectangle.setFillColor(sf::Color(127, 127, 127, 120));
    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("LeaveRoomButton")
    )->setCallback([this]
    {
        m_context.network.send(rtype::Protocol::LEAVE_ROOM);
        m_context.stateManager.popCurrentState(); // Clears PauseState
        m_context.stateManager.navigate(States::ID::Menu); // ClearsGameState
    });
}

bool PauseState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            m_context.stateManager.popCurrentState();
        }
    }
    AMenuState::handleEvent(event);
    return false;
}

void PauseState::draw(void)
{
    m_context.window.draw(m_blurRectangle);
    AMenuState::draw();
}