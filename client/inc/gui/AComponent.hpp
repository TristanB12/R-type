/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Component
*/

#pragma once

#include <memory>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

#define PERCENTAGE(percentage, nb) ((nb * percentage) / 100)

namespace sf
{
    class Event;
}

namespace gui {
struct Margin {
    unsigned int left;
    unsigned int top;
    unsigned int right;
    unsigned int bottom;
};

enum class HorizontalAlignement {
    LEFT,
    CENTER,
    RIGHT
};

enum class VerticalAlignement {
    TOP,
    CENTER,
    BOTTOM
};

class AComponent : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
    typedef std::shared_ptr<AComponent> Ptr;

    virtual ~AComponent(void) = default;

    bool isSelected(void) const
    {
        return m_isSelected;
    }
    virtual void select(void)
    {
        m_isSelected = true;
    }
    virtual void deselect(void)
    {
        m_isSelected = false;
    }

    virtual bool isActive(void) const
    {
        return m_isActive;
    }

    virtual void activate(void)
    {
        m_isActive = true;
    }

    virtual void deactivate(void)
    {
        m_isActive = false;
    }

    bool isVisible(void) const
    {
        return m_isVisible;
    }

    virtual void setVisible(bool isVisible)
    {
        m_isVisible = isVisible;
    }

    virtual void setAlignement(VerticalAlignement verticalAlignement,
        HorizontalAlignement horizontalAlignement)
    {
        m_verticalAlignement = verticalAlignement;
        m_horizontalAlignement = horizontalAlignement;
    }

    virtual void setVerticalAlignement(VerticalAlignement verticalAlignement)
    {
        m_verticalAlignement = verticalAlignement;
    }

    virtual void setHorizontalAlignement(HorizontalAlignement horizontalAlignement)
    {
        m_horizontalAlignement = horizontalAlignement;
    }

    virtual VerticalAlignement getVerticalAlignement(void) const
    {
        return m_verticalAlignement;
    }

    virtual HorizontalAlignement getHorizontalAlignement(void) const
    {
        return m_horizontalAlignement;
    }

    virtual void setMargin(const Margin &margin)
    {
        m_margin = margin;
    }

    virtual void setMarginLeft(unsigned int marginleft)
    {
        m_margin.left = marginleft;
    }

    virtual void setMarginTop(unsigned int marginTop)
    {
        m_margin.top = marginTop;
    }

    virtual void setMarginRight(unsigned int marginRight)
    {
        m_margin.right = marginRight;
    }

    virtual void setMarginBottom(unsigned int marginBottom)
    {
        m_margin.bottom = marginBottom;
    }

    virtual Margin getMargin(void) const
    {
        return m_margin;
    }

    virtual sf::Vector2u getSize(void) const = 0;
    virtual bool isSelectable(void) const = 0;
    virtual void handleEvent(const sf::Event &event) = 0;

private:
    bool m_isSelected = false;
    bool m_isActive = false;
    bool m_isVisible = true;
    VerticalAlignement m_verticalAlignement = VerticalAlignement::TOP;
    HorizontalAlignement m_horizontalAlignement = HorizontalAlignement::LEFT;
    Margin m_margin{0, 0, 0, 0};
};
} // namespace gui
