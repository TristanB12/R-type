/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** PauseState
*/

#pragma once

#include "AMenuState.hpp"

class PauseState : public AMenuState {
public:
    PauseState(SharedContext &context);
    virtual ~PauseState(void) = default;

    bool handleEvent(const sf::Event &event) override;
    void draw(void) override;

private:
    sf::RectangleShape m_blurRectangle;
};
