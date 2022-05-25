/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** RtypeCoordinator
*/

#pragma once

#include "ecs/generic/Coordinator.hpp"
#include "ecs/specific/System/RenderSystem.hpp"
#include "ecs/specific/System/PhysicSystem.hpp"
#include "ecs/specific/System/collisionSystem.hpp"
#include "ecs/specific/System/ennemyBehaviorSystem.hpp"
#include "ecs/specific/System/SpawnEnnemySystem.hpp"
#include "ecs/specific/System/manageProjectileSystem.hpp"

class RtypeCoordinator : public Coordinator {
 public:
    RtypeCoordinator(void) : Coordinator()
    {
        registerComponent<Position>();
        registerComponent<Drawable>();
        registerComponent<Move>();
        registerComponent<Hitbox>();
        registerComponent<Ennemy>();

        registerSystem<RenderSystem>();
        getSystem<RenderSystem>()->init(*this);

        registerSystem<PhysicSystem>();
        getSystem<PhysicSystem>()->init(*this);

        registerSystem<CollisionSystem>();
        getSystem<CollisionSystem>()->init(*this);

        registerSystem<EnnemyBehavior>();
        getSystem<EnnemyBehavior>()->init(*this);  

        registerSystem<SpawnEnnemies>();
        getSystem<SpawnEnnemies>()->init(*this);   

        registerSystem<manageProjectileSystem>();
        getSystem<manageProjectileSystem>()->init(*this);   
    }

    ~RtypeCoordinator(void) = default;
};
