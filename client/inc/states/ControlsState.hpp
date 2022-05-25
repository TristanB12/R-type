/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ControlsState
*/

#pragma once

#include "AMenuState.hpp"

class ControlsState : public AMenuState {
public:
    ControlsState(SharedContext &context);
    virtual ~ControlsState(void) = default;
};
