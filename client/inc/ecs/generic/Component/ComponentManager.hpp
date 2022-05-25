/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** ComponentManager
*/

#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "ecs/generic/Component/ComponentArray.hpp"
#include "ecs/generic/ECSError.hpp"
#include "ecs/generic/Component/Component.hpp"

class ComponentManager {
public:

    template<typename T>
	void registerComponent(void)
	{
		std::string typeName = typeid(T).name();

    	if (m_componentTypes.find(typeName) != m_componentTypes.end()) {
        	throw ComponentTypeError("Registering component type more than once.");
    	}
		m_componentTypes.insert({typeName, m_nextComponentType});
		m_componentArray.insert({typeName, std::make_shared<ComponentArray<T>>()});
		m_nextComponentType++;
	}

	template<typename T>
	componentType getComponentType(void)
	{
		std::string typeName = typeid(T).name();

    	if (m_componentTypes.find(typeName) == m_componentTypes.end()) {
    	    throw ComponentTypeError("Component not registered before use.");
    	}
		return m_componentTypes[typeName];
	}

	template<typename T>
	void addComponent(const Entity &entity, T component)
	{
	    getComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	void removeComponent(const Entity &entity)
	{
	    getComponentArray<T>()->removeData(entity);
	}

	template<typename T>
	T& getComponent(const Entity &entity)
	{
	    return getComponentArray<T>()->getData(entity);
	}

	void entityDestroyed(const Entity &entity)
	{
	    for (auto const &pair: m_componentArray) {
	        auto const &component = pair.second;
	        component->entityDestroyed(entity);
	    }
	}

private:
    template<typename T>
    std::shared_ptr<ComponentArray<T> > getComponentArray(void)
    {
        std::string typeName = typeid(T).name();

        if (m_componentTypes.find(typeName) == m_componentTypes.end())
            throw ComponentTypeError("Component not registered before use.");
        return std::static_pointer_cast<ComponentArray<T>>(m_componentArray[typeName]);
    }

    std::unordered_map<std::string, componentType>                      m_componentTypes{};
    std::unordered_map<std::string, std::shared_ptr<IComponentArray> >  m_componentArray{};
    componentType                                                       m_nextComponentType{};

};