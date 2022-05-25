/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** MenuState
*/

#pragma once

#include "AMenuState.hpp"

class MenuState : public AMenuState {
public:
    MenuState(SharedContext &context);
    virtual ~MenuState(void) = default;
};