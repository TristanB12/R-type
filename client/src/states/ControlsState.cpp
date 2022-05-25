/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** ControlsState
*/

#include "ControlsState.hpp"
#include "StateManager.hpp"

ControlsState::ControlsState(SharedContext &context) :
    AMenuState(context, "Controls.conf")
{
    std::dynamic_pointer_cast<gui::Button>(
        AMenuState::getComponent("GoBackButton")
    )->setCallback([this] () {
        m_context.stateManager.navigate(States::ID::Menu);
    });
}
