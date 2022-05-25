/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** AMenuState
*/

#pragma once

#include "AState.hpp"
#include "StateLoader.hpp"
#include "Container.hpp"
#include "Utils.hpp"

// Parent class of all rtype menus
class AMenuState : public AState {
public:
    virtual ~AMenuState(void) = default;

    virtual bool handleEvent(const sf::Event &event)
    {
        m_guiContainer.handleEvent(event);
        return true;
    }

    virtual bool update(sf::Time dt)
    {
        (void)dt;
        return true;
    }

    virtual void draw(void) override
    {
        m_context.window.draw(m_guiContainer);
    }

protected:
    AMenuState(
        SharedContext &context,
        const std::string &stateConfigFilename = ""
    ) : AState(context),
        m_guiContainer(context.window.getSize())
    {
        if (stateConfigFilename.empty()) {
            return;
        }
        gui::StateLoader loader(context.ressources);
        m_components = loader.loadGuiFromFile(
            STATE_CONFIG_DIR_PATH + stateConfigFilename
        );

        for (const auto &[name, component] : m_components) {
            AMenuState::addGUIComponent(name, component);
        }
    }

    void addGUIComponent(gui::AComponent::Ptr component)
    {
        m_guiContainer.addComponent(component);
    }

    void addGUIComponent(const std::string &name, gui::AComponent::Ptr component)
    {
        m_guiContainer.addComponent(name, component);
    }

    gui::AComponent::Ptr getComponent(const std::string &name)
    {
        return m_components[name];
    }

private:
    const std::string STATE_CONFIG_DIR_PATH = "./configurations/gui/";
    gui::StateLoader::components_map m_components;
    gui::Container m_guiContainer;
};
