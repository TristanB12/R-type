/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** AState
*/

#ifndef ASTATE_HPP_
#define ASTATE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include "SharedContext.hpp"

#define SET_TCP_HANDLER(protocol, handler) \
(m_context.network.setHandler(rtype::Protocol::protocol, [this] (Packet<rtype::Protocol> &response) { this->handler(response); }))

#define SET_UDP_HANDLER(protocol, handler) \
(m_context.network.setHandler(rtype::IngameProtocol::protocol, [this] (Packet<rtype::IngameProtocol> &response) { this->handler(response); }))

class AState {
public:
    using Ptr = std::unique_ptr<AState>;

    virtual ~AState(void) = default;

    virtual bool handleEvent(const sf::Event &event) = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual void draw() = 0;

protected:
    AState(SharedContext &context) : m_context(context) {}

    SharedContext &m_context;
};

#endif /* !ASTATE_HPP_ */
