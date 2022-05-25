/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** StackPanel
*/

#include "StackPanel.hpp"

namespace gui {
unsigned int StackPanel::getMaxWidth(void) const
{
    auto widestComponent = std::max_element(m_children.begin(), m_children.end(),
        [] (const AComponent::Ptr &componentA, const AComponent::Ptr &componentB) {
        return componentA->getSize().x <= componentB->getSize().x;
    });

    return (widestComponent == m_children.end()) ? 0 : (*widestComponent)->getSize().x;
}

void StackPanel::updateChildPositions(void)
{
    float y = 0.0f;
    sf::Vector2u containerSize = this->getSize();

    for (const AComponent::Ptr &component : this->m_children) {
        /*
            In a vertical stack panel, a vertical alignement doesn't make sense.
            Items are aligned vertically by the order they were packed in, separated by a gap.
        */
        float x = Container::getPositionByAlignement(
            component->getVerticalAlignement(),
            component->getHorizontalAlignement(),
            containerSize,
            component->getSize()
        ).x;
        Margin margin = component->getMargin();

        component->setPosition({
            x + margin.left - margin.right,
            y + margin.top - margin.bottom
        });
        y += component->getSize().y + m_gap;
    }
}
} // namespace gui
