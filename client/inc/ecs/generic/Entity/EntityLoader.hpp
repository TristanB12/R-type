/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** EntityLoader
*/

#ifndef ENTITYLOADER_HPP_
#define ENTITYLOADER_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include "Entity.hpp"
#include "ecs/specific/RtypeCoordinator.hpp"


class EntityLoader {
public:
    inline EntityLoader(RtypeCoordinator &coordinator)
        : m_coordinator(coordinator), m_directoryPath("../client/configurations/entities/"), m_controllers(componentsControllers())
    {};
    inline EntityLoader(RtypeCoordinator &coordinator, std::string directoryPath)
        : m_coordinator(coordinator), m_directoryPath(directoryPath), m_controllers(componentsControllers())
    {};
    inline ~EntityLoader() {};

    Entity loadEntityFromFile(std::string fileName, const std::string &name = "");
    void loadAllEntities(void);
private:
    struct Component {
        std::string name;
        std::vector<std::string> params;
    };

    using components_controllers = std::unordered_map<std::string, std::function<void (Entity, EntityLoader::Component)>>;
    EntityLoader::components_controllers componentsControllers(void);

    // functions to manage components
    void processPosition(Entity e, EntityLoader::Component component);
    void processMove(Entity e, EntityLoader::Component component);
    void processDrawable(Entity e, EntityLoader::Component component);
    void processHitboxes(Entity e, EntityLoader::Component component);
    void processEnnemies(Entity e, EntityLoader::Component component);

    std::pair<int, int> getPosition(const char *str);
    std::vector<EntityLoader::Component> splitInComponents(std::vector<std::string> fileContent);
    std::vector<std::string> removeEmptyLines(std::vector<std::string> fileContent);
    std::string getFilePathFromName(std::string fileName);
    std::vector<std::string> readFile(std::string fileName);

    RtypeCoordinator &m_coordinator;
    std::string m_directoryPath;
    EntityLoader::components_controllers m_controllers;
};

#endif /* !ENTITYLOADER_HPP_ */
