/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** System
*/

#pragma once

#include <set>
#include "ecs/generic/Entity/Entity.hpp"

class System {
 public:
	virtual ~System(void) = default;

	std::set<Entity> m_entities;
};