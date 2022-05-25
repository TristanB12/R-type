/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Utils
*/

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

inline void centerOrigin(sf::Sprite &sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                    std::floor(bounds.top + bounds.height / 2.f));
}

inline void centerOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                std::floor(bounds.top + bounds.height / 2.f));
}

inline void scaleBackground(sf::Sprite &sprite, const sf::Vector2u &windowSize)
{
    sprite.setScale(
        windowSize.x / sprite.getLocalBounds().width,
        windowSize.y / sprite.getLocalBounds().height);
}

inline sf::Vector2u boundsToSize(const sf::FloatRect &bounds)
{
    return sf::Vector2u{
        static_cast<unsigned int>(bounds.width),
        static_cast<unsigned int>(bounds.height)
    };
}

inline int calcPercentage(int percentage, int number)
{
    return (number * percentage) / 100;
}

inline unsigned int calcPercentage(unsigned int percentage, unsigned int number)
{
    return (number * percentage) / 100;
}

inline float calcPercentage(float percentage, float number)
{
    return (number * percentage) / 100;
}