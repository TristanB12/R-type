/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** StateStack
*/

#include <iostream>
#include "StateStack.hpp"

AState::Ptr StateStack::createState(States::ID stateID)
{
    // find the factory function of the state constructor
    auto found = m_factory.find(stateID);

    if (found == m_factory.end()) {
        std::cerr << "State nb " << int(stateID) << " not registered" << std::endl;
        return nullptr;
    }
    return found->second();
}

void StateStack::applyPendingChanges()
{
    AState::Ptr newState = nullptr;
    for (const PendingChange &change : m_pendingChanges)
    {
        switch (change.action)
        {
            case StateStack::Action::PUSH:
                newState = createState(change.stateID);
                if (newState != nullptr) {
                    m_stack.push_back(std::move(newState));
                    m_currentStateID = change.stateID;
                }
                break;

            case StateStack::Action::POP:
                if (!m_stack.empty()) {
                    m_stack.pop_back();
                }
                break;

            case StateStack::Action::CLEAR:
                m_stack.clear();
                break;
        }
    }
    m_pendingChanges.clear();
}