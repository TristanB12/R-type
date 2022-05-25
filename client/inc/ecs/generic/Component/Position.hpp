/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <string>
#include <iostream>
#include "Vector.hpp"

class Position : public Vector<double> {
 public:
    Position(double x = 0.f, double y = 0.f, double z = 0.f);

    std::string to_string(void) const;

    friend std::ostream &operator<<(std::ostream& cout, const Position &pos)
    {
        cout << pos.to_string();
        return cout;
    }
};

#endif /* !POSITION_HPP_ */