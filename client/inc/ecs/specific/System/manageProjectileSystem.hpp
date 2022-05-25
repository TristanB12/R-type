/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** manageProjectileSystem
*/

#pragma once

#include "ecs/generic/System/System.hpp"
#include "ecs/generic/Coordinator.hpp"
#include "ecs/generic/Component/Position.hpp"
#include "ecs/generic/Entity/EntitiesFlyWeight.hpp"
#include "ecs/generic/Component/Drawable.hpp"
#include "ecs/generic/Component/Move.hpp"

class manageProjectileSystem : public System {
 public:

    void init(Coordinator &coordinator)
    {
        Signature signature;

        signature.set(coordinator.getComponentType<Position>());
        coordinator.setSystemSignature<manageProjectileSystem>(signature);
    }

    void update(Coordinator &coordinator, EntitiesFlyWeight &playerProjectiles)
    {
        for (auto &e : playerProjectiles.getEntities()) {
            if (e.second.isAvailable)
                continue;
            Entity entity = Entity(e.second.entity);
            Position &pos = coordinator.getComponent<Position>(entity);
            Drawable &draw = coordinator.getComponent<Drawable>(entity);
            Move &move = coordinator.getComponent<Move>(entity);
            if (pos.x > 1400) {
                draw.image.isVisible = false;
                playerProjectiles.setEntityAvailability(entity, true);
                pos.x = -100;
                pos.y = -100;
                move.type = Move::NONE;
            }
        }
    }
};
