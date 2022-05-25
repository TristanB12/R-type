/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Container
*/

#include <functional>
#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include "Container.hpp"

namespace gui {
Container::Container(const sf::Vector2u &size) :
    m_size(size)
{
    m_eventHandlers = {
        { sf::Event::KeyReleased, &Container::handleKeyReleasedEvent },
        { sf::Event::MouseMoved, &Container::handleMouseMovedEvent },
        { sf::Event::MouseButtonReleased, &Container::handleMouseButtonReleasedEvent },
        { sf::Event::JoystickButtonPressed, &Container::handleJoystickButtonPressedEvent },
        { sf::Event::JoystickMoved, &Container::handleJoystickMovedEvent }
    };
}

void Container::deselect(void)
{
    AComponent::deselect();
    if (this->hasSelection()) {
        m_children[m_selectedChildIndex]->deselect();
    }
    m_selectedChildIndex = -1;
}

void Container::addComponent(const std::string &name, AComponent::Ptr component)
{
    m_childrenMap[name] = component;
    this->addComponent(component);
}

void Container::addComponent(AComponent::Ptr component)
{
    m_children.push_back(component);
    if (m_childrenVerticalAlignement.has_value()) {
        component->setVerticalAlignement(m_childrenVerticalAlignement.value());
    }
    if (m_childrenHorizontalAlignement.has_value()) {
        component->setHorizontalAlignement(m_childrenHorizontalAlignement.value());
    }
    this->updateChildPosition(component);
    if (component->isSelectable()) {
        this->m_isSelectable = true;
    }
}

AComponent::Ptr Container::getComponent(const std::string &name)
{
    return m_childrenMap[name];
}

// AComponent::Ptr Container::getSelectedComponent(void)
// {
//     auto castContainer = [] (const AComponent::Ptr &component) {
//         return std::dynamic_pointer_cast<Container>(component);
//     };

//     if (!this->isSelectable() || !this->hasSelection()) {
//         return nullptr;
//     }
//     auto container = castContainer(m_children[m_selectedChildIndex]);
//     if (container != nullptr) {
//         return container->getSelectedComponent();
//     }
//     return m_children[m_selectedChildIndex];
// }

void Container::removeComponent(AComponent::Ptr component)
{
    auto it = std::find(m_children.begin(), m_children.end(), component);
    if (it != m_children.end()) {
        m_children.erase(it);
    }
    auto cit = std::find_if(m_childrenMap.begin(), m_childrenMap.end(),
        [component] (const auto &childComponentPair) {
            return component == childComponentPair.second;
    });
    if (cit != m_childrenMap.end()) {
        m_childrenMap.erase(cit);
    }
}

void Container::handleEvent(const sf::Event &event)
{
    for (const auto &[eventType, handler] : m_eventHandlers) {
        if (event.type == eventType) {
            std::invoke(handler, this, event);
        }
    }
    if (this->hasSelection())
    {
        m_children[m_selectedChildIndex]->handleEvent(event);
    }
}

void Container::handleMouseMovedEvent(const sf::Event &event)
{
    sf::Vector2u mousePos(event.mouseMove.x, event.mouseMove.y);
    sf::Rect<unsigned int> hitbox(sf::Vector2u(this->getPosition()), this->getSize());

    if (!hitbox.contains(mousePos)) {
        this->deselect();
        return;
    }
    for (const AComponent::Ptr &component : m_children) {
        sf::Rect<unsigned int> hitbox(
            sf::Vector2u(this->getPosition() + component->getPosition()),
            component->getSize()
        );
        if (hitbox.contains(mousePos)) {
            auto it = std::find(m_children.begin(), m_children.end(), component);
            size_t index = std::distance(m_children.begin(), it);
            this->select(index);
        } else {
            component->deselect();
        }
    }
}

void Container::handleMouseButtonReleasedEvent(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left && this->hasSelection())
    {
        m_children[m_selectedChildIndex]->activate();
    }
}

void Container::handleKeyReleasedEvent(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Up) {
        this->selectPrevious();
    } else if (event.key.code == sf::Keyboard::Down) {
        this->selectNext();
    } else if (event.key.code == sf::Keyboard::Return) {
        if (this->hasSelection()) {
            m_children[m_selectedChildIndex]->activate();
        }
    }
}

void Container::handleJoystickMovedEvent(const sf::Event &event)
{
    if (event.joystickMove.axis == sf::Joystick::Y)
    {
        if (event.joystickMove.position < -95.0f) {
            this->selectPrevious();
        } else if (event.joystickMove.position > 95.0f) {
            this->selectNext();
        }
    }
}

void Container::handleJoystickButtonPressedEvent(const sf::Event &event)
{
    if (event.joystickButton.button == 0 && this->hasSelection()) {
        m_children[m_selectedChildIndex]->activate();
    }
}

void Container::select(const std::size_t &index)
{
    if (index >= m_children.size() || !m_children[index]->isSelectable())
    {
        return;
    }
    if (this->hasSelection()) {
        m_children[m_selectedChildIndex]->deselect();
    }
    m_children[index]->select();
    m_selectedChildIndex = index;
}

void Container::selectNext(void)
{
    auto castContainer = [] (const AComponent::Ptr &component) {
        return std::dynamic_pointer_cast<Container>(component);
    };

    if (!this->hasSelection()) {
        this->selectNextIndex();
        return;
    }
    auto container = castContainer(m_children[m_selectedChildIndex]);
    if (container == nullptr || container->selectedIsLast()) {
        this->selectNextIndex();
    }
}

void Container::selectPrevious(void)
{
    auto castContainer = [] (const AComponent::Ptr &component) {
        return std::dynamic_pointer_cast<Container>(component);
    };

    if (!this->hasSelection()) {
        this->selectNextIndex();
    }
    auto container = castContainer(m_children[m_selectedChildIndex]);
    if (container == nullptr || container->selectedIsFirst()) {
        this->selectPreviousIndex();
    }
}

void Container::selectNextIndex(void)
{
    if (!this->isSelectable()) {
        return;
    }

    // Search next component that is selectable, wrap around if necessary
    int nextIndex = m_selectedChildIndex;
    do {
        nextIndex = (nextIndex + 1) % m_children.size();
    } while (!m_children[nextIndex]->isSelectable());

    this->select(nextIndex);
}

void Container::selectPreviousIndex(void)
{
    if (!this->isSelectable()) {
        return;
    }

    // Search previous component that is selectable, wrap around if necessary
    int prevIndex = m_selectedChildIndex;
    do {
        prevIndex = (prevIndex + m_children.size() - 1) % m_children.size();
    } while (!m_children[prevIndex]->isSelectable());

    this->select(prevIndex);
}

bool Container::selectedIsFirst(void)
{
    if (!this->hasSelection()) {
        return false;
    }
    for (int i = m_selectedChildIndex - 1 ; i >= 0 ; i--) {
        if (m_children[i]->isSelectable()) {
            return false;
        }
    }
    return true;
}

bool Container::selectedIsLast(void)
{
    if (!this->hasSelection()) {
        return false;
    }
    int size = m_children.size();
    for (int i = m_selectedChildIndex + 1 ; i < size ; i++) {
        if (m_children[i]->isSelectable()) {
            return false;
        }
    }
    return true;
}

void Container::setChildrenAlignement(VerticalAlignement verticalAlignement,
        HorizontalAlignement horizontalAlignement)
{
    m_childrenVerticalAlignement.emplace(verticalAlignement);
    m_childrenHorizontalAlignement.emplace(horizontalAlignement);
    for (const AComponent::Ptr &component : m_children) {
        component->setAlignement(verticalAlignement, horizontalAlignement);
        this->updateChildPosition(component);
    }
}

void Container::setChildrenVerticalAlignement(VerticalAlignement verticalAlignement)
{
    m_childrenVerticalAlignement.emplace(verticalAlignement);
    for (const AComponent::Ptr &component : m_children) {
        component->setVerticalAlignement(verticalAlignement);
        this->updateChildPosition(component);
    }
}

void Container::setChildrenHorizontalAlignement(HorizontalAlignement horizontalAlignement)
{
    m_childrenHorizontalAlignement.emplace(horizontalAlignement);
    for (const AComponent::Ptr &component : m_children) {
        component->setHorizontalAlignement(horizontalAlignement);
        this->updateChildPosition(component);
    }
}

void Container::updateChildPosition(AComponent::Ptr component)
{
    sf::Vector2f pos = this->getPositionByAlignement(
        component->getVerticalAlignement(),
        component->getHorizontalAlignement(),
        m_size,
        component->getSize()
    );
    Margin margin = component->getMargin();

    component->setPosition({
        pos.x + margin.left - margin.right,
        pos.y + margin.top - margin.bottom
    });
}

sf::Vector2f Container::getPositionByAlignement(
    VerticalAlignement verticalAlignement,
    HorizontalAlignement horizontalAlignement,
    const sf::Vector2u &containerSize,
    const sf::Vector2u &componentSize
)
{
    auto container = sf::Rect<unsigned int>({0, 0}, containerSize);
    auto component = sf::Rect<unsigned int>({0, 0}, componentSize);

    std::unordered_map<VerticalAlignement, float> y;
    y[VerticalAlignement::TOP] = 0.0f;
    y[VerticalAlignement::CENTER] = container.height / 2 - (component.height / 2);
    y[VerticalAlignement::BOTTOM] = container.height - component.height;

    std::unordered_map<HorizontalAlignement, float> x;
    x[HorizontalAlignement::LEFT] = 0.0f;
    x[HorizontalAlignement::CENTER] = container.width / 2 - (component.width / 2);
    x[HorizontalAlignement::RIGHT] = container.width - component.width;

    return sf::Vector2f{x[horizontalAlignement], y[verticalAlignement]};
}

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    // sf::RectangleShape shape;
    // shape.setFillColor(sf::Color::Transparent);
    // shape.setOutlineColor(sf::Color::Red);
    // shape.setOutlineThickness(1.0f);
    for (const AComponent::Ptr &component : m_children) {
        // shape.setPosition(component->getPosition());
        // shape.setSize(sf::Vector2f(component->getSize()));
        // target.draw(shape, states);
        if (component->isVisible()) {
            target.draw(*component, states);
        }
    }
}
} // namespace gui
