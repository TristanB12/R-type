/*
** EPITECH PROJECT, 2021
** B-CPP-501-RUN-5-1-rtype-julien.pause
** File description:
** Component
*/

#pragma once

#include <stddef.h>
#include <bitset>

#define MAX_COMPONENTS      32  // Max components can be created in one game

using Signature     =   std::bitset<MAX_COMPONENTS>;
using componentType =   std::uint8_t;