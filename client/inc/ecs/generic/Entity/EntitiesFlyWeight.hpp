/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** EntitiesFlyWeight
*/

#pragma once

#include <unordered_map>
#include <string>
#include "ecs/generic/Entity/Entity.hpp"
#include "ecs/generic/Coordinator.hpp"

class EntitiesFlyWeight {
 public:

    typedef struct available_entities_s {
        size_t entity;
        bool isAvailable = true;
    } available_entities_t;

    using map_available_entities_u = std::unordered_map<size_t, available_entities_t>;
 
    EntitiesFlyWeight(Coordinator &coordinator);

    virtual ~EntitiesFlyWeight(void) = default;

    template<typename F>
    void build(size_t n, const std::string &tag, F &&lambda)
    {
        for (size_t i = 0; i < n; i++) {
            Entity entity = m_coordinator.createEntity(tag + std::to_string(i));
            lambda(entity, m_coordinator);
            addEntity(entity);
        }
    }

    void addEntity(Entity entity, bool available = true);

    Entity getAvailableEntity(void);

    size_t getUsedEntities(void) const;

    void setEntityAvailability(Entity entity, bool available);

    map_available_entities_u &getEntities(void);

 protected:
    Coordinator&                m_coordinator;
    map_available_entities_u    m_entities;
};