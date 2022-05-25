/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** GuiLoader
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include "RessourceManager.hpp"
#include "AComponent.hpp"
#include "Button.hpp"
#include "StackPanel.hpp"
#include "Label.hpp"
#include "Container.hpp"
#include "Sprite.hpp"
#include "TextField.hpp"

namespace gui {
class StateLoader {
public:
    StateLoader(RessourceManager &manager)
        : m_ressources(manager)
    {};
    virtual ~StateLoader() = default;

    using components_map = std::unordered_map<std::string, AComponent::Ptr>;

    components_map loadGuiFromFile(std::string filePath);

private:
    void parseComponents(std::vector<std::string> fileContent);

    std::vector<std::string> removeEmptyLines(std::vector<std::string> fileContent);
    std::vector<std::string> readFile(std::string fileName);
    std::vector<std::string> splitArgs(std::string line);

    size_t replaceString(std::string &str, const std::string &search, const std::string &replace);
    std::string &trimString(std::string &str);
    inline bool startsWith(std::string str, std::string start) {return (str.rfind(start, 0) == 0);};

    gui::HorizontalAlignement getHorizontalAlignementFromString(std::string str);
    gui::VerticalAlignement getVerticalAlignementFromString(std::string str);
    gui::Margin getMargin(std::vector<std::string> &vectMargin, size_t i);

    template <typename SingleComponent>
    void processSingleComponent(std::string line, gui::StackPanel::Ptr parent);

    void processSprite(std::string line, gui::StackPanel::Ptr parent);
    void processTextfield(std::string line, gui::StackPanel::Ptr parent);
    int processStackPannel(std::string line, gui::StackPanel::Ptr &container);

    components_map m_components;
    RessourceManager &m_ressources;
};
} // namespace gui
