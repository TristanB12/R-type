/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** CreditsState
*/

#pragma once

#include "AMenuState.hpp"

class CreditsState : public AMenuState {
public:
    CreditsState(SharedContext &context);
    virtual ~CreditsState(void) = default;
};
