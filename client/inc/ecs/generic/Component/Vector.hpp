/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <stddef.h>

template <typename T>
class Vector {
 public:
    Vector(const T &x = 0, const T &y = 0, const T &z = 0) :  x(x), y(y), z(z) {}

    virtual ~Vector(void) = default;

    template<typename U>
    Vector(const Vector<U> &other)
    {
        *this = other;
    }

    template<typename U>
    Vector<T> &operator=(const Vector<U> &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;   
        return *this;
    }

    template<typename U>
    Vector<T> &operator=(const U &value)
    {
        x = value;
        y = value;
        z = value;
        return *this;
    }

    template<typename U>
    Vector<T> operator-(const Vector<U> &other)
    {
        return Vector<T>(x - other.x, y - other.y, z - other.z);
    }

    template<typename U>
    Vector<T> operator*(const U &mul)
    {
        return Vector<T>(x * mul, y * mul, z * mul);
    }

    template<typename U>
    Vector<T> operator+(const Vector<U> &other)
    {
        return Vector<T>(x + other.x, y + other.y, z + other.z);
    }

    template<typename U>
    bool operator==(const Vector<U> &other)
    {
        return x == other.x && y == other.y && z == other.z;
    }

    template<typename U>
    bool operator!=(const Vector<U> &other)
    {
        return !(*this == other);
    }

    template<typename U>
    bool operator>=(const Vector<U> &other)
    {
        return x >= other.x && y >= other.y && z >= other.z;
    }

    template<typename U>
    Vector<T> &operator+=(const Vector<U> &other)
    {
        return (*this = *this + other);        
    }

    T x;
    T y;
    T z;
};

#endif /* !VECTOR_HPP_ */