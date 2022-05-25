/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AClient
*/

#pragma once

#include <memory>

class AClient : public std::enable_shared_from_this<AClient> {
public:
    virtual ~AClient(void) = default;
};