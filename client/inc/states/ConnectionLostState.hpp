/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ConnectionLost
*/

#pragma once

#include "AMenuState.hpp"

class ConnectionLostState : public AMenuState {
public:
    ConnectionLostState(SharedContext &context);
    virtual ~ConnectionLostState(void) = default;

    bool handleEvent(const sf::Event &event)
    {
        AMenuState::handleEvent(event);
        return false;
    }

    bool update(sf::Time dt) override
    {
        (void)dt;
        return false;
    }

    void draw(void) override;

private:
    sf::RectangleShape m_blurRectangle;
};
