/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** EntitiesFlyWeight
*/

#include "ecs/generic/Entity/EntitiesFlyWeight.hpp"

EntitiesFlyWeight::EntitiesFlyWeight(Coordinator &coordinator)
 : m_coordinator(coordinator) {}

void EntitiesFlyWeight::addEntity(Entity entity, bool available) {
    m_entities[entity] = available_entities_t{entity, available};
}

Entity EntitiesFlyWeight::getAvailableEntity(void)
{
    for (auto &element: m_entities) {
        if (element.second.isAvailable) {
            element.second.isAvailable = false;
            return Entity(element.second.entity);
        }
    }
    throw EntitiesFlyWeightError("No entity available.");
}

void EntitiesFlyWeight::setEntityAvailability(Entity entity, bool available)
{
    if (m_entities.find(entity) == m_entities.end()) {
        throw EntityIDError("Retrieving non-existent entity.");
    }
    m_entities[entity].isAvailable = available;
}

EntitiesFlyWeight::map_available_entities_u &EntitiesFlyWeight::getEntities(void)
{
    return m_entities;
}

size_t EntitiesFlyWeight::getUsedEntities(void) const
{
    size_t used = 0;
    for (auto &elem : m_entities) {
        if (!elem.second.isAvailable) {
            used++;
        }
    }
    return used;
}
