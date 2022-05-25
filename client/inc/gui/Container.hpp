/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Container
*/

#pragma once

#include <iostream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <string>
#include "AComponent.hpp"

namespace gui {
class Container : public AComponent {
public:
    using Ptr = std::shared_ptr<Container>;

    Container(const sf::Vector2u &size = sf::Vector2u{0, 0});
    virtual ~Container(void) = default;

    inline virtual bool isSelectable(void) const override
    {
        return m_isSelectable;
    }
    virtual void deselect(void) override;
    virtual void handleEvent(const sf::Event &event) override;
    inline virtual sf::Vector2u getSize(void) const override
    {
        return m_size;
    }

    virtual void addComponent(const std::string &name, AComponent::Ptr component);
    virtual void addComponent(AComponent::Ptr component);
    virtual AComponent::Ptr getComponent(const std::string &name);
    virtual void removeComponent(AComponent::Ptr component);

    Container &operator<<(AComponent::Ptr component)
    {
        this->addComponent(component);
        return *this;
    }

    void clear(void)
    {
        m_children.clear();
    }
    bool selectedIsFirst(void);
    bool selectedIsLast(void);

    std::vector<AComponent::Ptr> getChildren(void) const
    {
        return m_children;
    }

    size_t getNbChildren(void) const
    {
        return m_children.size();
    }

    virtual void setChildrenAlignement(VerticalAlignement verticalAlignement,
        HorizontalAlignement horizontalAlignement);
    virtual void setChildrenVerticalAlignement(VerticalAlignement verticalAlignement);
    virtual void setChildrenHorizontalAlignement(HorizontalAlignement horizontalAlignement);

protected:
    std::vector<AComponent::Ptr> m_children;
    std::unordered_map<std::string, AComponent::Ptr> m_childrenMap;

    sf::Vector2f getPositionByAlignement(
        VerticalAlignement verticalAlignement,
        HorizontalAlignement horizontalAlignement,
        const sf::Vector2u &containerSize,
        const sf::Vector2u &componentSize
    );

private:
    void updateChildPosition(AComponent::Ptr component);
    bool hasSelection(void) const
    {
        return m_selectedChildIndex >= 0;
    }
    void select(const std::size_t &index);
    void selectNext(void);
    void selectPrevious(void);
    void selectNextIndex(void);
    void selectPreviousIndex(void);

    using handleEventFunc_t = void (Container::*)(const sf::Event &event);
    void handleMouseMovedEvent(const sf::Event &event);
    void handleMouseButtonReleasedEvent(const sf::Event &event);
    void handleKeyReleasedEvent(const sf::Event &event);
    void handleJoystickMovedEvent(const sf::Event &event);
    void handleJoystickButtonPressedEvent(const sf::Event &event);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2u m_size{0, 0};
    int m_selectedChildIndex = -1;
    bool m_isSelectable = false;

    std::unordered_map<sf::Event::EventType, handleEventFunc_t> m_eventHandlers;
    std::optional<VerticalAlignement> m_childrenVerticalAlignement = std::nullopt;
    std::optional<HorizontalAlignement> m_childrenHorizontalAlignement = std::nullopt;
}; // class Container
} // namespace gui
