/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

template <typename T>
class Rect {
 public:
    T top;
    T left;
    T width;
    T height;

    Rect(const T &top, const T &left, const T &width, const T &height)
     :  top(top), left(left), width(width), height(height) {}

    template<typename U>
    Rect<T> &operator=(const Rect<U> &other)
    {
       this->top = other.top;
       this->left = other.left;
       this->width = other.width;
       this->height = other.height;
       return *this;
    }

    template<typename U>
    Rect<T> operator+(const Rect<U> &other)
    {
       return Rect<T>(this->top + other.top, this->left + other.left, this->width + other.width, this->height + other.height);
    }

    template<typename U>
    Rect<T> &operator+=(const Rect<U> &other)
    {
       *this = *this + other;
       return *this;
    }

    template<typename U>
    Rect<T> operator-(const Rect<U> &other)
    {
       return Rect<T>(this->top - other.top, this->left - other.left, this->width - other.width, this->height - other.height);
    }

    template<typename U>
    Rect<T> &operator-=(const Rect<U> &other)
    {
       *this = *this - other;
       return *this;
    }
};

#endif /* !RECT_HPP_ */