/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Move
*/

#include "ecs/generic/Component/Move.hpp"

Move::Move(const MovementType &type)
 :  type(type) {}

Vector<double> Move::getNormalizedVector(Vector<double> const &vector)
{
    Vector<double> newVec;

    newVec.x = (vector.x > 0) ? 1 : vector.x;
    newVec.x = (vector.x < 0) ? -1 : newVec.x;
    newVec.y = (vector.y > 0) ? 1 : vector.y;
    newVec.y = (vector.y < 0) ? -1 : newVec.y;
    newVec.z = (vector.z > 0) ? 1 : vector.z;
    newVec.z = (vector.z < 0) ? -1 : newVec.z;
    return newVec;
}