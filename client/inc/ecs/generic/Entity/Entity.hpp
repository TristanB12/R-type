/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Entity
*/

#pragma once

#include <stddef.h>

#define MAX_ENTITIES        5000    // Max entities in the screen at the same time

using entityType    =   size_t;

class Entity {
public:
    explicit Entity(const entityType id) : m_id(id) {}
    virtual ~Entity(void) = default;

    operator entityType(void) const
    {
        return m_id;
    }
protected:
    entityType m_id = 0;
};