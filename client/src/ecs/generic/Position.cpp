/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Position
*/

#include "ecs/generic/Component/Position.hpp"

Position::Position(double x, double y, double z)
 :  Vector(x, y, z) {}

std::string Position::to_string(void) const
{
    std::string str = "[POSITION]: x('" +
        std::to_string(this->x) + "') y('" +
        std::to_string(this->y) + "') z('" +
        std::to_string(this->z) + "')";
    return str;
}