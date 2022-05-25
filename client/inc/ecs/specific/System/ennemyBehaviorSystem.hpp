/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** ennemyBehaviorSystem
*/

#pragma once

#include "ecs/generic/System/System.hpp"
#include "ecs/generic/Component/Drawable.hpp"
#include "ecs/generic/Component/Position.hpp"
#include "ecs/generic/Component/Ennemy.hpp"
#include "ecs/generic/Component/Move.hpp"
#include "ecs/generic/Entity/EntitiesFlyWeight.hpp"
#include <fstream>

class EnnemyBehavior : public System {
    public:
        void init(Coordinator &coordinator)
        {
            Signature signature;

            signature.set(coordinator.getComponentType<Ennemy>());
            signature.set(coordinator.getComponentType<Move>());
            signature.set(coordinator.getComponentType<Drawable>());
            coordinator.setSystemSignature<EnnemyBehavior>(signature);
        }

        void update(Coordinator &coordinator, const sf::Clock &clock, EntitiesFlyWeight &ennemies)
        {
            float seconds = clock.getElapsedTime().asSeconds();
            if (seconds - _duration > 2.0) {
                for (auto &element: ennemies.getEntities()) {
                    if (element.second.isAvailable)
                        continue;
                    auto entity = Entity(element.second.entity);
                    auto& ennemy = coordinator.getComponent<Ennemy>(entity);
                    auto& move = coordinator.getComponent<Move>(entity);

                    std::cout << "moving one ennemy" << std::endl;
                    std::vector<std::pair<int, int>> positions = ennemy.getMoves();
                    ennemy.setMove();
                    move.type = Move::TARGET;
                    move.targetPosition.x = positions.at(ennemy.getCurrentMove()).first;
                    move.targetPosition.y = positions.at(ennemy.getCurrentMove()).second;
                    move.targetPosition.z = 0;
                }
                _duration = clock.getElapsedTime().asSeconds();
            }
        }
    private:
        float _duration = 0;
};