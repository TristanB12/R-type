/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Coordinator
*/

#pragma once

#include <memory>
#include "ecs/generic/Entity/EntityManager.hpp"
#include "ecs/generic/Component/ComponentManager.hpp"
#include "ecs/generic/System/SystemManager.hpp"

class Coordinator {
 public:
    Coordinator(void)
    {
        this->init();
    }

    virtual ~Coordinator(void) = default;

    Coordinator(const Coordinator &other) = delete;
    void operator=(const Coordinator &other) = delete;

    void init(void)
    {
        m_entityManager = std::make_unique<EntityManager>();
        m_componentManager = std::make_unique<ComponentManager>();
        m_systemManager = std::make_unique<SystemManager>();
    }

    Entity createEntity(const std::string &name)
    {
        return m_entityManager->createEntity(name);
    }

    void destroyEntity(Entity entity)
    {
        m_entityManager->destroyEntity(entity);
        m_componentManager->entityDestroyed(entity);
        m_systemManager->entityDestroyed(entity);
    }

    void destroyEntity(const std::string &name)
    {
        auto entity = getEntityByName(name);

        m_entityManager->destroyEntity(entity);
        m_componentManager->entityDestroyed(entity);
        m_systemManager->entityDestroyed(entity);
    }

    Entity getEntityByName(const std::string &name)
    {
        return m_entityManager->getEntityByName(name);
    }

    std::string getEntityName(const Entity &entity)
    {
        return m_entityManager->getEntityName(entity);
    }

	std::list<Entity> getEntitiesBySignature(const Signature &signature)
    {
        return m_entityManager->getEntitiesBySignature(signature);
    }

    template<typename T>
    void registerComponent(void)
    {
        m_componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        m_componentManager->addComponent<T>(entity, component);
        auto signature = m_entityManager->getSignature(entity);
        signature.set(m_componentManager->getComponentType<T>(), true);
        m_entityManager->setSignature(entity, signature);

        m_systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        m_componentManager->removeComponent<T>(entity);
        auto signature = m_entityManager->getSignature(entity);
        signature.set(m_componentManager->getComponentType<T>(), false);
        m_entityManager->setSignature(entity, signature);

        m_systemManager->entitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& getComponent(const std::string &name)
    {
        return m_componentManager->getComponent<T>(getEntityByName(name));
    }

    template<typename T>
    T& getComponent(Entity entity)
    {
        return m_componentManager->getComponent<T>(entity);
    }

    template<typename T>
    componentType getComponentType()
    {
        return m_componentManager->getComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> registerSystem(void)
    {
        auto sharedSystem = m_systemManager->registerSystem<T>();
        return sharedSystem;
    }

    template<typename T>
    void setSystemSignature(Signature signature)
    {
        m_systemManager->setSignature<T>(signature);
    }

    std::unordered_map<std::string, std::shared_ptr<System> > &getMapSystems(void)
    {
        return m_systemManager->getSystems();
    }

    template<typename T>
    std::shared_ptr<T> getSystem(void)
    {
        std::string name = typeid(T).name();

        auto systems = m_systemManager->getSystems();
        // TODO: Check if system tag exists
        auto sharedSystem =  std::dynamic_pointer_cast<T>(systems[name]);
        return sharedSystem;
    }

 protected:

    std::unique_ptr<ComponentManager>   m_componentManager;
    std::unique_ptr<EntityManager>      m_entityManager;
    std::unique_ptr<SystemManager>      m_systemManager;
};