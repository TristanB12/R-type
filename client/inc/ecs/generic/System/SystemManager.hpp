/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** SystemManager
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "ecs/generic/System/System.hpp"
#include "ecs/generic/Entity/Entity.hpp"
#include "ecs/generic/ECSError.hpp"

class SystemManager {
 public:
    
    template<typename T>
    std::shared_ptr<T> registerSystem(void)
    {
        std::string name = typeid(T).name();

        if (m_systems.find(name) != m_systems.end())
            throw SystemTypeError("Registering system more than once.");
        auto system = std::make_shared<T>();
        m_systems.insert({name, system});
        return system;
    }

    template<typename T>
    void setSignature(Signature signature)
    {
        std::string name = typeid(T).name();

        if (m_systems.find(name) == m_systems.end())
            throw SystemTypeError("System used before registered.");
        m_signatures.insert({name, signature});
    }

    void entityDestroyed(const Entity &entity)
    {
        for (auto const& pair: m_systems) {
            auto const& system = pair.second;
            system->m_entities.erase(entity);
        }
    }

    void entitySignatureChanged(const Entity &entity, Signature entitySignature)
    {
        for (auto const& pair : m_systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_signatures[type];

            if ((entitySignature & systemSignature) == systemSignature)
                system->m_entities.insert(entity);
            else
                system->m_entities.erase(entity);
        }
    }

    std::unordered_map<std::string, std::shared_ptr<System> > &getSystems(void)
    {
        return m_systems;
    }

 private:
    std::unordered_map<std::string, Signature>                  m_signatures{};
    std::unordered_map<std::string, std::shared_ptr<System> >   m_systems{};
};