/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** ParallaxState
*/

#pragma once

#include "AState.hpp"
#include "ecs/specific/RtypeCoordinator.hpp"

class ParallaxState : public AState {
 public:
    ParallaxState(SharedContext &context);
    virtual ~ParallaxState(void) = default;

    virtual bool handleEvent(const sf::Event &event) override final;
    virtual bool update(sf::Time dt) override final;
    virtual void draw(void) override final;

 private:
    RtypeCoordinator m_coordinator;
};