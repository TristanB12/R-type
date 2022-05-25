/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** Player
*/

#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

struct Player {
    enum class Color : uint8_t
    {
        BLUE,
        RED,
        YELLOW,
        GREEN
    };

    Player(void) = default;
    Player(int32_t id, Color color) : id(id), color(color) {}

    int32_t id;
    Color color;

    std::string colorToString(void) const {
        std::unordered_map<Color, std::string> colorMap = {
            { Color::BLUE, "BLUE" },
            { Color::RED, "RED" },
            { Color::YELLOW, "YELLOW" },
            { Color::GREEN, "GREEN" }
        };

        return colorMap[this->color];
    }

    friend std::ostream &operator<<(std::ostream &out, const Player &player)
    {
        return out << "Player " << player.id << " : " << player.colorToString();
    }
};

