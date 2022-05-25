/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** ECSError
*/

#pragma once

#include <exception>
#include <string>

class ECSError : public std::exception {
 public:
    ECSError(const std::string &message, const std::string &type = "ECSError: ")
        : _message(message), _type(type) {}

    virtual ~ECSError(void) {}

    const char *what(void) const throw() { return _message.c_str(); }

    std::string const &type(void) const { return _type; }

 protected:
    std::string _message;
    std::string _type;
 protected:
};

/*  ---- DEFINE EntityError ---- */

class EntityIndexError : public ECSError {
 public:
    EntityIndexError(const std::string &message,
                    const std::string &type = "EntityIndexError: ")
        : ECSError(message, type) {}

    ~EntityIndexError(void) {}
};

class EntityValueError : public ECSError {
 public:
    EntityValueError(const std::string &message,
                    const std::string &type = "EntityValueError: ")
        : ECSError(message, type) {}

    ~EntityValueError(void) {}
};

class EntityIDError : public ECSError {
 public:
    EntityIDError(const std::string &message,
                    const std::string &type = "EntityIDError: ")
        : ECSError(message, type) {}

    ~EntityIDError(void) {}
};

class EntityNameError : public ECSError {
 public:
    EntityNameError(const std::string &message,
                    const std::string &type = "EntityNameError: ")
        : ECSError(message, type) {}

    ~EntityNameError(void) {}
};

class EntitiesFlyWeightError : public ECSError {
 public:
    EntitiesFlyWeightError(const std::string &message,
                    const std::string &type = "EntitiesFlyWeightError: ")
        : ECSError(message, type) {}

    ~EntitiesFlyWeightError(void) {}
};

/*  ---- ENDIF EntityError ---- */

/*  ---- DEFINE ComponentError ---- */

class ComponentTypeError : public ECSError {
 public:
    ComponentTypeError(const std::string &message,
                    const std::string &type = "ComponentTypeError: ")
        : ECSError(message, type) {}

    ~ComponentTypeError(void) {}
};

/*  ---- ENDIF ComponentError ---- */

/*  ---- DEFINE SystemError ---- */

class SystemTypeError : public ECSError {
 public:
    SystemTypeError(const std::string &message,
                    const std::string &type = "SystemTypeError: ")
        : ECSError(message, type) {}

    ~SystemTypeError(void) {}
};

/*  ---- ENDIF SystemError ---- */