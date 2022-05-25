/*
** EPITECH PROJECT, 2021
** r-type [WSL: Ubuntu]
** File description:
** ServerError
*/

#ifndef SERVERERROR_HPP_
#define SERVERERROR_HPP_

#include <exception>
#include <string>

class ServerError : public std::exception {
public:
    explicit ServerError(std::string const &message) : _message(message) {}

    inline virtual const char* what() const noexcept {
        return _message.c_str();
    }

private:
    std::string _message;
};

class NotFoundError : public ServerError {
public:
    explicit NotFoundError(std::string const &message) : ServerError(message) {}
};


#endif /* !SERVERERROR_HPP_ */
