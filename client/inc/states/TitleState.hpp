/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** TitleState
*/

#pragma once

#include "AMenuState.hpp"
#include "Label.hpp"
#include "StateLoader.hpp"

class TitleState : public AMenuState {
public:
    TitleState(SharedContext &context) :
        AMenuState(context, "Title.conf")
    {
        m_context.audio.playMusic("paradise_warfare");
    }
    virtual ~TitleState(void) = default;

    virtual bool handleEvent(const sf::Event &event) override final;
    virtual bool update(sf::Time dt) override final;

private:
    bool m_showLabel = true;
    sf::Time m_labelEffectTime = sf::Time::Zero;
};