/*
** EPITECH PROJECT, 2021
** rtype [WSL: Ubuntu-20.04]
** File description:
** PlayerList
*/

#pragma once

#include "StackPanel.hpp"
#include "PlayerItem.hpp"

namespace gui {
class PlayerList : public AComponent {
public:
    using Ptr = std::shared_ptr<PlayerList>;

    PlayerList(void) = default;
    virtual ~PlayerList(void) = default;

    virtual sf::Vector2u getSize(void) const
    {
        return m_stackPanel.getSize();
    }

    virtual bool isSelectable(void) const
    {
        return false;
    }
    virtual void handleEvent(const sf::Event &event)
    {
        (void)event;
    }

    void addPlayer(PlayerItem::Ptr playerItem)
    {
        m_stackPanel.addComponent(playerItem);
    }

    void removePlayer(int id)
    {
        auto player = this->getPlayerByID(id);
        if (player) {
            m_stackPanel.removeComponent(player);
        }
    }

    void togglePlayerReady(int id)
    {
        auto player = this->getPlayerByID(id);
        if (player) {
            player->toggleReady();
        }
    }

    std::vector<struct Player> getPlayers(void) const {
        std::vector<struct Player> players;

        for (const AComponent::Ptr &component : m_stackPanel.getChildren()) {
            auto playerItem = std::dynamic_pointer_cast<PlayerItem>(component);
            players.push_back(playerItem->getPlayer());
        }
        return players;
    }

    size_t getNbPlayers(void) const
    {
        return m_stackPanel.getNbChildren();
    }

private:
    PlayerItem::Ptr getPlayerByID(int id)
    {
        auto playersItem = m_stackPanel.getChildren();
        auto it = std::find_if(playersItem.begin(), playersItem.end(),
            [id] (const AComponent::Ptr &component) {
                auto player = std::dynamic_pointer_cast<PlayerItem>(component);
                return player && player->getID() == id;
        });
        return (it == playersItem.end()) ? nullptr
            : std::dynamic_pointer_cast<PlayerItem>(*it);
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(m_stackPanel, states);
    }

    StackPanel m_stackPanel;
};

} // namespace gui

