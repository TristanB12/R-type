/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** GameLostState
*/

#pragma once

#include "AMenuState.hpp"

class GameLostState : public AMenuState {
public:
    GameLostState(SharedContext &context);
    virtual ~GameLostState(void);

    bool handleEvent(const sf::Event &event) override;
    void draw(void) override;

private:
    sf::RectangleShape m_blurRectangle;
};