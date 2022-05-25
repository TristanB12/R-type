/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** spawnPataPata
*/

#pragma once

#include "ecs/generic/System/System.hpp"
#include "ecs/generic/Component/Drawable.hpp"
#include "ecs/generic/Component/Position.hpp"
#include "ecs/generic/Component/Ennemy.hpp"
#include "ecs/generic/Coordinator.hpp"
#include "ecs/generic/Entity/EntitiesFlyWeight.hpp"

class SpawnEnnemies : public System
{
    public:
        void init(Coordinator &coordinator)
        {
            Signature signature;

            signature.set(coordinator.getComponentType<Drawable>());
            signature.set(coordinator.getComponentType<Position>());
            signature.set(coordinator.getComponentType<Ennemy>());
            coordinator.setSystemSignature<SpawnEnnemies>(signature);
        }
        
        void update(Coordinator &coordinator, const sf::Clock &clock, EntitiesFlyWeight &ennemies)
        {
            if (ennemies.getUsedEntities() == _maxEnnemies)
                return;
            float seconds = clock.getElapsedTime().asSeconds();
            if (seconds - _duration > 3.0) {
                Entity ennemy = ennemies.getAvailableEntity();
                coordinator.getComponent<Position>(ennemy).x = 1400;
                coordinator.getComponent<Position>(ennemy).y = 400;
                coordinator.getComponent<Drawable>(ennemy).image.isVisible = true;
                _duration = clock.getElapsedTime().asSeconds();
            }
        }
    private:
        size_t _maxEnnemies = 10;
        float _duration = 0;
};