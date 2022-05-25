/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** EntityManager
*/

#pragma once

#include <queue>
#include <array>
#include <iostream>
#include <unordered_map>
#include <list>
#include "Entity.hpp"
#include "ecs/generic/Component/Component.hpp"
#include "ecs/generic/ECSError.hpp"

class EntityManager {
 public:
    EntityManager(void);

    Entity createEntity(const std::string &name);

    void destroyEntity(const Entity &entity);

    Entity getEntityByName(const std::string &name);

    std::string getEntityName(const Entity &entity) const;

    void setSignature(const Entity &entity, Signature signature);

    Signature getSignature(const Entity &entity);

    std::list<Entity> getEntitiesBySignature(const Signature &signature);

 private:
    std::queue<Entity>                      m_entitiesAvailable{};
    std::array<Signature, MAX_ENTITIES>     m_signatures{};
    uint32_t                                m_entityCount = 0;
    std::unordered_map<std::string, size_t> m_entitiesCreated{};
};