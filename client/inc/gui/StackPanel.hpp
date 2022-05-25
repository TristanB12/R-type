/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** StackPanel
*/

#pragma once

#include "Container.hpp"

namespace gui {
// Vertical Stack Panel
class StackPanel : public Container {
public:
    using Ptr = std::shared_ptr<StackPanel>;

    StackPanel(void) = default;
    virtual ~StackPanel(void) = default;

    void addComponent(const std::string &name, AComponent::Ptr component) override
    {
        Container::addComponent(name, component);
        this->updateChildPositions();
    }

    void addComponent(AComponent::Ptr component) override
    {
        Container::addComponent(component);
        this->updateChildPositions();
    }

    void removeComponent(AComponent::Ptr component) override
    {
        Container::removeComponent(component);
        this->updateChildPositions();
    }

    void setGap(unsigned int gap)
    {
        m_gap = gap;
        this->updateChildPositions();
    }

    sf::Vector2u getSize(void) const override
    {
        unsigned int totalHeightGap = (m_children.size() == 0) ? 0
            : m_gap * static_cast<unsigned int>(m_children.size() - 1);
        sf::Vector2u totalSize{this->getMaxWidth(), totalHeightGap};

        for (const AComponent::Ptr &component : m_children) {
            totalSize.y += component->getSize().y;
        }
        return totalSize;
    }

    void setChildrenAlignement(VerticalAlignement verticalAlignement,
        HorizontalAlignement horizontalAlignement) override
    {
        Container::setChildrenAlignement(verticalAlignement, horizontalAlignement);
        this->updateChildPositions();
    }

    void setChildrenVerticalAlignement(VerticalAlignement verticalAlignement) override
    {
        Container::setChildrenVerticalAlignement(verticalAlignement);
        this->updateChildPositions();
    }

    void setChildrenHorizontalAlignement(HorizontalAlignement horizontalAlignement) override
    {
        Container::setChildrenHorizontalAlignement(horizontalAlignement);
        this->updateChildPositions();
    }

private:
    void updateChildPositions(void);
    unsigned int getMaxWidth(void) const;

    unsigned int m_gap = 0;
};
} // namespace gui

