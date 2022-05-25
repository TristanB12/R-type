/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** CreditsState
*/

#include "CreditsState.hpp"
#include "StateManager.hpp"

CreditsState::CreditsState(SharedContext &context) :
    AMenuState(context, "Credits.conf")
{
    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("GoBackButton")
    )->setCallback([this] () {
        m_context.stateManager.navigate(States::ID::Menu);
    });
}
