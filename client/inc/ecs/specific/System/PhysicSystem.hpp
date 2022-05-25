/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** PhysicSystem
*/

#pragma once

#include <stdlib.h>
#include "ecs/generic/System/System.hpp"
#include "ecs/generic/Coordinator.hpp"
#include "ecs/generic/Component/Position.hpp"
#include "ecs/generic/Component/Move.hpp"
#include "ecs/generic/Component/Hitbox.hpp"

class PhysicSystem : public System {
 public:

    void init(Coordinator &coordinator)
    {
        Signature signature;

        signature.set(coordinator.getComponentType<Position>());
        signature.set(coordinator.getComponentType<Move>());
        coordinator.setSystemSignature<PhysicSystem>(signature);
    }

    void update(Coordinator &coordinator)
    {
        for (Entity const &entity: m_entities) {
            Position &pos = coordinator.getComponent<Position>(entity);
            Move &move = coordinator.getComponent<Move>(entity);

            if (move.type == Move::ACCELERATION) {
                move.velocity += move.acceleration;
                move.acceleration = 0;
            }
            if (move.type == Move::TARGET) {
                Vector<double> vector = move.targetPosition - pos;
                if (abs(vector.x) <= 5 && abs(vector.x) >= 0 && abs(vector.y) <= 5 && abs(vector.y) >= 0) {
                    move.type = Move::NONE;
                } else {
                    move.velocity += move.getNormalizedVector(vector);
                }
            }
            pos.x += move.velocity.x;
            pos.y += move.velocity.y;
            move.velocity = move.velocity * 0.94;
        }
    }
};
