/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** ParallaxState
*/

#include "ParallaxState.hpp"

ParallaxState::ParallaxState(SharedContext &context) :
    AState(context)
{
    Entity e2 = m_coordinator.createEntity("bg1");
    Drawable draw2 = Drawable("nebula", true);

    m_context.ressources.getTexture("nebula").setRepeated(true);
    m_coordinator.addComponent(e2, Position());

    draw2.isAnimated = true;
    draw2.currentAnimation = "default";
    draw2.animations["default"].frames.push_back(Rect<int>(0, 0, 1280, 720));
    draw2.animations["default"].isParallax = true;
    draw2.animations["default"].parallaxOffset = Rect<int>(1, 0, 0, 0);

    Entity e3 = m_coordinator.createEntity("bg2");
    Drawable draw3 = Drawable("stars", true);

    m_context.ressources.getTexture("stars").setRepeated(true);
    m_coordinator.addComponent(e3, Position());

    draw3.isAnimated = true;
    draw3.currentAnimation = "default";
    draw3.animations["default"].frames.push_back(Rect<int>(0, 0, 1280, 720));
    draw3.animations["default"].isParallax = true;
    draw3.animations["default"].parallaxOffset = Rect<int>(2, 0, 0, 0);

    Entity e4 = m_coordinator.createEntity("ships");
    Drawable draw4 = Drawable("bg_ships", true);

    m_context.ressources.getTexture("bg_ships").setRepeated(true);
    m_coordinator.addComponent(e4, Position());

    draw4.currentAnimation = "default";
    draw4.animations["default"].frames.push_back(Rect<int>(0, 0, 2000, 720));
    draw4.animations["default"].isParallax = true;
    draw4.animations["default"].parallaxOffset = Rect<int>(3, 0, 0, 0);

    m_coordinator.addComponent(e3, draw3);
    // m_coordinator.addComponent(e4, draw4);
    m_coordinator.addComponent(e2, draw2);
}

bool ParallaxState::handleEvent(const sf::Event &event)
{
    (void)event;
    return true;
}

bool ParallaxState::update(sf::Time dt)
{
    (void)dt;
    return true;
}

void ParallaxState::draw(void)
{
    m_coordinator.getSystem<RenderSystem>()->update(m_coordinator, m_context);
}