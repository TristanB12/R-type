/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** StateStack
*/

#ifndef STATESTACK_HPP_
#define STATESTACK_HPP_

#include <vector>
#include <functional>
#include <unordered_map>
#include "SharedContext.hpp"
#include "AState.hpp"
#include "StatesID.hpp"

class StateStack {
public:
    enum Action {
        PUSH,
        POP,
        CLEAR
    };

    explicit StateStack(SharedContext context) : m_context(context) {}
    StateStack(const StateStack &other) = delete;
    StateStack &operator=(const StateStack &other) = delete;

    virtual ~StateStack(void) = default;

    template <typename T>
    void registerState(States::ID stateID)
    {
        m_factory[stateID] = [this] () {
            return AState::Ptr(new T(m_context));
        };
    }

    void handleEvent(const sf::Event &event)
    {
        for (auto itr = m_stack.rbegin() ; itr != m_stack.rend() ; ++itr)
        {
            if ((*itr)->handleEvent(event) == false) {
                break;
            }
        }
        applyPendingChanges();
    }

    void update(sf::Time dt)
    {
        for (auto itr = m_stack.rbegin() ; itr != m_stack.rend() ; ++itr)
        {
            if ((*itr)->update(dt) == false) {
                break;
            }
        }
        applyPendingChanges();
    }

    void draw(void)
    {
        for (const AState::Ptr &state : m_stack) {
            state->draw();
        }
    }

    void pushState(States::ID stateID)
    {
        m_pendingChanges.push_back(PendingChange(PUSH, stateID));
    }

    void popState(void)
    {
        m_pendingChanges.push_back(PendingChange(POP));
    }

    void clearStates(void)
    {
        m_pendingChanges.push_back(PendingChange(CLEAR));
    }

    bool isEmpty(void) const
    {
        return m_stack.empty();
    }

    States::ID getCurrentStateID(void) const
    {
        return m_currentStateID;
    }

private:
    struct PendingChange {
        PendingChange(Action action, States::ID stateID = States::ID::None) :
            action(action),
            stateID(stateID)
        {}

        Action action;
        States::ID stateID;
    };

    AState::Ptr createState(States::ID stateId);
    void applyPendingChanges(void);

    std::vector<AState::Ptr> m_stack;
    SharedContext m_context;
    std::vector<PendingChange> m_pendingChanges;
    std::unordered_map<States::ID, std::function<AState::Ptr()>> m_factory;
    States::ID m_currentStateID = States::ID::None;
};

#endif /* !STATESTACK_HPP_ */
