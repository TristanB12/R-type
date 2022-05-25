/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** ComponentArray
*/

#pragma once

#include <array>
#include <unordered_map>
#include "ecs/generic/Entity/Entity.hpp"
#include "ecs/generic/ECSError.hpp"

class IComponentArray {
 public:
	virtual ~IComponentArray(void) = default;
	virtual void entityDestroyed(const Entity &entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void insertData(const Entity &entity, T component)
	{
		size_t newIndex = m_size;

        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
            throw EntityIDError("Component added to same entity('"+ std::to_string(entity) +"') more than once.");
		m_entityToIndexMap[entity] = newIndex;
		m_indexToEntityMap[newIndex] = entity;
		m_componentArray[newIndex] = component;
		m_size++;
	}

	void removeData(const Entity &entity)
	{
        size_t indexOfRemovedEntity = 0;
        size_t indexOfLastElement = 0;

        if (m_entityToIndexMap.find(entity) == m_entityToIndexMap.end())
            throw EntityIDError("Removing non-existent component.");
		indexOfRemovedEntity = m_entityToIndexMap[entity];
		indexOfLastElement = m_size - 1;
		m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];
		size_t entityIdOfLastElement = m_indexToEntityMap[indexOfLastElement];
		Entity entityOfLastElement(entityIdOfLastElement);
        m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
		m_entityToIndexMap.erase(entity);
		m_indexToEntityMap.erase(indexOfLastElement);
		m_size--;
	}

	T& getData(const Entity &entity)
	{
        if (m_entityToIndexMap.find(entity) == m_entityToIndexMap.end())
            throw EntityIDError("Retrieving non-existent component in entity.");
		return m_componentArray[m_entityToIndexMap[entity]];
	}

	void entityDestroyed(const Entity &entity) override
	{
		if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
			removeData(entity);
	}

private:
	std::array<T, MAX_ENTITIES>             m_componentArray{};
	std::unordered_map<entityType, size_t>  m_entityToIndexMap{};
	std::unordered_map<size_t, entityType>  m_indexToEntityMap{};
	size_t m_size = 0;
};