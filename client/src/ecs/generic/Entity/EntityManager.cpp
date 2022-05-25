/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** EntityManager
*/

#include "ecs/generic/Entity/EntityManager.hpp"

EntityManager::EntityManager(void)
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
		m_entitiesAvailable.push(Entity(i));
}

Entity EntityManager::createEntity(const std::string &name)
{
    if (m_entityCount >= MAX_ENTITIES)
        throw EntityValueError("Too many entities in existence.");

    Entity entity = m_entitiesAvailable.front();
    m_entitiesAvailable.pop();
    m_entityCount++;
    m_entitiesCreated.insert({name, entity});
    return entity;
}

void EntityManager::destroyEntity(const Entity &entity)
{
    if (entity >= MAX_ENTITIES)
        throw EntityIndexError("Entity out of range.");
    m_entitiesCreated.erase(getEntityName(entity));
    m_signatures[entity].reset();
    m_entitiesAvailable.push(entity);
    m_entityCount--;
}

Entity EntityManager::getEntityByName(const std::string &name)
{
    if (m_entitiesCreated.find(name) == m_entitiesCreated.end())
        throw EntityNameError("Entity with name '" + name + "' doesn't exist.");
    return Entity(m_entitiesCreated[name]);
}

std::string EntityManager::getEntityName(const Entity &entity) const
{
    if (entity >= MAX_ENTITIES)
        throw EntityIndexError("Entity out of range.");
    for (auto it: m_entitiesCreated) {
        if (it.second == entity)
            return it.first;
    }
    throw EntityIDError("Entity '" + std::to_string(entity) + "' doesn't exist.");
}

void EntityManager::setSignature(const Entity &entity, Signature signature)
{
    if (entity >= MAX_ENTITIES)
        throw EntityIndexError("Entity out of range.");
    m_signatures[entity] = signature;
}

Signature EntityManager::getSignature(const Entity &entity)
{
    if (entity >= MAX_ENTITIES)
        throw EntityIndexError("Entity out of range.");
    return m_signatures[entity];
}

std::list<Entity> EntityManager::getEntitiesBySignature(const Signature &signature)
{
    std::list<Entity> entities;

    for (auto it: m_entitiesCreated) {
        Entity entity = Entity(it.second);
        if ((getSignature(entity) & signature) == signature)
            entities.push_back(entity);
    }
    return entities;
}