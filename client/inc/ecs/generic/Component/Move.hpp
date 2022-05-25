/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** move
*/

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "Vector.hpp"

class Move {
public:
    enum MovementType {
        NONE,
        TARGET,
        ACCELERATION
    };

    Vector<double>  targetPosition;
    Vector<double>  acceleration;
    Vector<double>  velocity;
    MovementType    type;

    Move(const MovementType &type = NONE);

    Vector<double> getNormalizedVector(Vector<double> const &vector);
};

#endif /* !MOVE_HPP_ */