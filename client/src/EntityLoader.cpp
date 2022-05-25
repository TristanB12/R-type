/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** EntityLoader
*/

#include "EntityLoader.hpp"
#include "Ennemy.hpp"

EntityLoader::components_controllers EntityLoader::componentsControllers(void) {
    return {
        {std::string("POSITION"),
            [this] (Entity e, EntityLoader::Component component) {this->processPosition(e, component);}},
        {std::string("MOVE"),
            [this] (Entity e, EntityLoader::Component component) {this->processMove(e, component);}},
        {std::string("DRAWABLE"),
            [this] (Entity e, EntityLoader::Component component) {this->processDrawable(e, component);}},
        {std::string("HITBOX"),
            [this] (Entity e, EntityLoader::Component component) {this->processHitboxes(e, component);}},
        {std::string("ENNEMY"),
            [this] (Entity e, EntityLoader::Component component) {this->processEnnemies(e, component);}}
    };
}

Entity EntityLoader::loadEntityFromFile(std::string fileName, const std::string &name) {
    std::vector<std::string> fileContent = removeEmptyLines(readFile(fileName));
    if(fileContent.size() <= 0)
        return Entity(0);
    std::vector<EntityLoader::Component> components = splitInComponents(fileContent);
    Entity e = m_coordinator.createEntity(name == "" ? fileContent.at(0) : name);

    std::cout << "Entity created: " << (name == "" ? fileContent.at(0) : name) << std::endl;
    for (auto component : components) {
        if (m_controllers.find(component.name) != m_controllers.end())
            m_controllers[component.name](e, component);
    }
    return e;
}

void EntityLoader::loadAllEntities(void) {
    std::string filePath;
    std::string fileName;

    for (auto const file : std::filesystem::directory_iterator(m_directoryPath)) {
        filePath = file.path().string();
        fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
        loadEntityFromFile(fileName);
    }
}

std::vector<EntityLoader::Component> EntityLoader::splitInComponents(std::vector<std::string> fileContent) {
    std::vector<EntityLoader::Component> components;
    EntityLoader::Component component;

    for (auto line : fileContent) {
        if (line.at(0) == '#') {
            components.push_back(component);
            component.params.clear();
            component.name = line.erase(0, 1);
        } else {
            component.params.push_back(line);
        }
    }
    components.push_back(component);
    if (components.size() > 0)
        components.erase(components.begin());
    return components;
}

std::vector<std::string> EntityLoader::removeEmptyLines(std::vector<std::string> fileContent) {
    std::vector<std::string> withoutEmptyLines;

    for (auto line : fileContent) {
        if (!line.empty())
            withoutEmptyLines.push_back(line);
    }
    return withoutEmptyLines;
}

std::string EntityLoader::getFilePathFromName(std::string fileName) {
    return m_directoryPath + fileName; 
}

std::vector<std::string> EntityLoader::readFile(std::string fileName) {
    std::string filePath = getFilePathFromName(fileName);
    std::string line;
    std::vector<std::string> fileContent;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Can not open file." << std::endl;
        return fileContent;
    }
    while (std::getline(file, line)) {
        fileContent.push_back(line);
    }
    file.close();
    return fileContent;
}

void EntityLoader::processPosition(Entity e, EntityLoader::Component component) {
    char *coords = strdup(component.params.at(0).c_str());
    double x = std::stod(std::strtok(coords, ":"));
    double y = std::stod(std::strtok(NULL, ":"));
    double z = std::stod(std::strtok(NULL, ":"));

    m_coordinator.addComponent(e, Position(x, y, z));
    free(coords);
}

void EntityLoader::processMove(Entity e, EntityLoader::Component component) {
    Move::MovementType type;

    if (component.params.at(0) == "acceleration")
        type = Move::ACCELERATION;
    if (component.params.at(0) == "target")
        type = Move::TARGET;
    if (component.params.at(0) == "none")
        type = Move::NONE;
    m_coordinator.addComponent(e, Move(type));
}

void EntityLoader::processDrawable(Entity e, EntityLoader::Component component) {
    std::string animationName;
    Rect<int> rect(0, 0, 0, 0);
    bool isVisible = false;
    if (component.params.at(1) == "true")
        isVisible = true;
    Drawable draw = Drawable(component.params.at(0), isVisible);

    if (component.params.at(2) == "true")
        draw.isAnimated = true;
    draw.currentAnimation = component.params.at(3);

    for (size_t i = 4; i < component.params.size(); i++) {
        if (component.params.at(i).at(0) == '$') {
            animationName = component.params.at(i++).erase(0, 1);
            draw.animations[animationName].isLoop = component.params.at(i) == "true" ? true : false;
        } else {
            char *rectCoords = strdup(component.params.at(i).c_str());
            rect.top = std::stoi(std::strtok(rectCoords, ":"));
            rect.left = std::stoi(std::strtok(NULL, ":"));
            rect.width = std::stoi(std::strtok(NULL, ":"));
            rect.height = std::stoi(std::strtok(NULL, ":"));
            draw.animations[animationName].frames.push_back(rect);
        }
    }
    m_coordinator.addComponent(e, draw);
}


void EntityLoader::processHitboxes(Entity e, EntityLoader::Component component) {
    int type = std::stoi(std::strtok(const_cast<char *>(component.params.at(0).c_str()), ":"));
    int friendly = std::stoi(std::strtok(NULL, ":"));
    Hitbox box(friendly, type);
    
    m_coordinator.addComponent(e, box);
}

std::pair<int, int> EntityLoader::getPosition(const char *str) {
    int x = std::stoi(std::strtok(const_cast<char *>(str), ":"));
    int y = std::stoi(std::strtok(NULL, ":"));
    std::pair<int, int> pos = std::pair<int, int>(x, y);
    
    return pos;
}

void EntityLoader::processEnnemies(Entity e, EntityLoader::Component component) {
    int hp = std::stoi(const_cast<char *>(component.params.at(0).c_str()));
    std::vector<std::pair<int, int>> targets;
    targets.push_back(getPosition(component.params.at(1).c_str()));
    targets.push_back(getPosition(component.params.at(2).c_str()));
    targets.push_back(getPosition(component.params.at(3).c_str()));
    targets.push_back(getPosition(component.params.at(4).c_str()));

    Ennemy ennemy(hp, targets);

    m_coordinator.addComponent(e, ennemy);
}