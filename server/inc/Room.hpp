/*
** EPITECH PROJECT, 2021
** r-type [WSL: Ubuntu]
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include "RtypeClient.hpp"

class Room {
public:
    Room(const std::string &roomName, int id) :
        m_id(id),
        m_roomName(roomName)
    {}
    virtual ~Room() = default;

    /*          getters         */
    inline int getId(void) {return m_id;};
    inline std::string getRoomName(void) {return m_roomName;};
    inline size_t getNbPlayer(void) { return m_players.size(); }
    std::vector<std::shared_ptr<rtype::Client>> getPlayers(void) {return m_players;};

    /*      other methods       */
    inline void addPlayer(std::shared_ptr<rtype::Client> client)
    {
        m_players.push_back(client);
    }
    inline void removePlayer(std::shared_ptr<rtype::Client> client)
    {
        m_players.erase(std::remove(m_players.begin(), m_players.end(), client));
    }
    inline bool isRoomReady(void)
    {
        for (auto player : m_players) {
            if (!player->isReady()) {
                return false;
            }
        }
        return true;
    }
    inline bool isStarted(void) {return m_isStarted;};
    inline void startRoom() {m_isStarted = true;};

private:
    int m_id;
    bool m_isStarted = false;
    std::string m_roomName;
    std::vector<std::shared_ptr<rtype::Client>> m_players;
};

#endif /* !ROOM_HPP_ */
