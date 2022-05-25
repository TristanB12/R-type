/*
** EPITECH PROJECT, 2021
** r-type [WSL: Ubuntu]
** File description:
** TestRoom
*/

#include <gtest/gtest.h>
#include "Room.hpp"

TEST(server_tests, BasicAssertions) {
    std::string roomName("test room");
    int roomId = 42;

    Room room(roomName, 42);
    EXPECT_EQ(room.getId(), roomId);
    EXPECT_EQ(room.getRoomName(), roomName);
}
