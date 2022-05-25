/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** StateLoader
*/

#include "StateLoader.hpp"

gui::StateLoader::components_map gui::StateLoader::loadGuiFromFile(std::string filePath) {
    std::vector<std::string> fileContent = readFile(filePath);

    m_components.clear();
    if (fileContent.size() > 0)
        parseComponents(fileContent);
    return m_components;
}

void gui::StateLoader::parseComponents(std::vector<std::string> fileContent) {
    gui::StackPanel::Ptr parent = nullptr;
    int nbChilds = 0;

    for (auto line : fileContent) {
        if (nbChilds == 0) {
            parent = nullptr;
        } else {
            nbChilds--;
        }
        if (startsWith(line, "Label")) {
            processSingleComponent<gui::Label>(line, parent);
        } else if (startsWith(line, "Button")) {
            processSingleComponent<gui::Button>(line, parent);
        } else if (startsWith(line, "Sprite")) {
            processSprite(line, parent);
        } else if (startsWith(line, "TextField")) {
            processTextfield(line, parent);
        } else if (startsWith(line, "StackPanel")) {
            nbChilds = processStackPannel(line, parent);
        }
    }
}

std::vector<std::string> gui::StateLoader::removeEmptyLines(std::vector<std::string> fileContent) {
    std::vector<std::string> withoutEmptyLines;

    for (auto line : fileContent) {
        if (!line.empty())
            withoutEmptyLines.push_back(line);
    }
    return withoutEmptyLines;
}

std::vector<std::string> gui::StateLoader::readFile(std::string filePath) {;
    std::string line;
    std::vector<std::string> fileContent;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Can not open file." << std::endl;
        return fileContent;
    }
    while (std::getline(file, line)) {
        fileContent.push_back(trimString(line));
    }
    file.close();
    return fileContent;
}

size_t gui::StateLoader::replaceString(std::string &str, const std::string &search, const std::string &replace)
{
    size_t count = 0;

    for (size_t pos = 0; (pos = str.find(search, pos)) != std::string::npos; count++, pos+=replace.length())
        str.replace(pos, search.length(), replace);
    return count;
}

std::string &gui::StateLoader::trimString(std::string &str)
{
    replaceString(str, "\t", " ");
    while (replaceString(str, "  ", " "));
    if (!str.empty()) {
        if (str.back() == ' ')
            str.pop_back();
        if (!str.empty() && str.front() == ' ')
            str.erase(str.begin());
    }
    return str;
}

std::vector<std::string> gui::StateLoader::splitArgs(std::string line) {
    size_t pos = line.find(' ');
    size_t initialPos = 0;
    std::vector<std::string> args;

    while (pos != std::string::npos) {
        if (line.at(initialPos) == '\"') {
            initialPos++;
            pos = initialPos;
            while (line.at(pos) != '\"') {
                pos++;
            }
        }
        args.push_back(line.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
        pos = line.find(' ', initialPos);
        if (pos > line.find('\"', initialPos))
            pos = line.find('\"', initialPos);
    }
    args.push_back(line.substr(initialPos, std::min(pos, line.size()) - initialPos + 1));
    return removeEmptyLines(args);
}

gui::HorizontalAlignement gui::StateLoader::getHorizontalAlignementFromString(std::string str) {
    std::unordered_map<std::string, gui::HorizontalAlignement> map {
        {"CENTER", gui::HorizontalAlignement::CENTER},
        {"LEFT", gui::HorizontalAlignement::LEFT},
        {"RIGHT", gui::HorizontalAlignement::RIGHT},
    };

    return map[str];
}

gui::VerticalAlignement gui::StateLoader::getVerticalAlignementFromString(std::string str) {
    std::unordered_map<std::string, gui::VerticalAlignement> map {
        {"CENTER", gui::VerticalAlignement::CENTER},
        {"BOTTOM", gui::VerticalAlignement::BOTTOM},
        {"TOP", gui::VerticalAlignement::TOP},
    };

    return map[str];
}

gui::Margin gui::StateLoader::getMargin(std::vector<std::string> &vectMargin, size_t i) {
    gui::Margin margin;

    margin.left = std::atoi(vectMargin.at(i).c_str());
    margin.top = std::atoi(vectMargin.at(i + 1).c_str());
    margin.right = std::atoi(vectMargin.at(i + 2).c_str());
    margin.bottom = std::atoi(vectMargin.at(i + 3).c_str());
    return margin;
}

template <typename SingleComponent>
void gui::StateLoader::processSingleComponent(std::string line,  gui::StackPanel::Ptr parent) {
    std::vector<std::string> args = splitArgs(line);

    auto comp = std::make_shared<SingleComponent>(args.at(2), m_ressources);
    bool hasAligned = false;
    for (size_t i = 3; i < args.size(); i++) {
        if (std::isdigit(args.at(i).at(0))) {
            comp->setMargin(getMargin(args, i));
            i += 3;
        }
        else {
            if (hasAligned)
                comp->setHorizontalAlignement(getHorizontalAlignementFromString(args.at(i)));
            else {
                comp->setVerticalAlignement(getVerticalAlignementFromString(args.at(i)));
                hasAligned = true;
            }
        }
    }
    std::string name = args.at(1);
    if (parent) {
        parent->addComponent(name, comp);
    } else {
        m_components[name] = comp;
    }
}

void gui::StateLoader::processSprite(std::string line,  gui::StackPanel::Ptr parent) {
    std::vector<std::string> args = splitArgs(line);

    auto comp = std::make_shared<gui::Sprite>(m_ressources.getTexture(args.at(2)));
    bool hasAligned = false;
    for (size_t i = 3; i < args.size(); i++) {
        if (std::isdigit(args.at(i).at(0))) {
            comp->setMargin(getMargin(args, i));
            i += 3;
        }
        else {
            if (hasAligned)
                comp->setHorizontalAlignement(getHorizontalAlignementFromString(args.at(i)));
            else {
                comp->setVerticalAlignement(getVerticalAlignementFromString(args.at(i)));
                hasAligned = true;
            }
        }
    }
    std::string name = args.at(1);
    if (parent)
        parent->addComponent(name, comp);
    else
        m_components[name] = comp;
}

void gui::StateLoader::processTextfield(std::string line,  gui::StackPanel::Ptr parent) {
    std::vector<std::string> args = splitArgs(line);

    auto comp = std::make_shared<gui::TextField>(std::atoi(args.at(2).c_str()), m_ressources.getDefaultFont());
    bool hasAligned = false;
    for (size_t i = 3; i < args.size(); i++) {
        if (std::isdigit(args.at(i).at(0))) {
            comp->setMargin(getMargin(args, i));
            i += 3;
        }
        else {
            if (hasAligned)
                comp->setHorizontalAlignement(getHorizontalAlignementFromString(args.at(i)));
            else {
                comp->setVerticalAlignement(getVerticalAlignementFromString(args.at(i)));
                hasAligned = true;
            }
        }
    }
    std::string name = args.at(1);
    if (parent) {
        parent->addComponent(name, comp);
    }
    else
        m_components[name] = comp;
}

int gui::StateLoader::processStackPannel(std::string line,  gui::StackPanel::Ptr &container) {
    std::vector<std::string> args = splitArgs(line);
    bool hasAligned = false;
    bool hasFlex = false;
    bool hasMargin = false;
    int nbChild = std::atoi(args.at(1).c_str());

    container = std::make_shared<gui::StackPanel>();
    for (size_t i = 3; i < args.size(); i++) {
        if (std::isdigit(args.at(i).at(0)) && i != args.size() - 1 && !hasMargin) {
            container->setMargin(getMargin(args, i));
            hasMargin = true;
            i += 3;
        }
        else if (std::isdigit(args.at(i).at(0))) {
            container->setGap(std::atoi(args.at(i).c_str()));
        }
        else {
            if (hasAligned && !hasFlex) {
                container->setHorizontalAlignement(getHorizontalAlignementFromString(args.at(i)));
                hasFlex = true;
            }
            else if (!hasAligned && !hasFlex) {
                container->setVerticalAlignement(getVerticalAlignementFromString(args.at(i)));
                hasAligned = true;
            } else {
                container->setChildrenHorizontalAlignement(getHorizontalAlignementFromString(args.at(i)));
            }
        }
    }
    m_components[args.at(2)] = container;
    return nbChild;
}