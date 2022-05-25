/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** main
*/

#include <cstdlib>
#include "Game.hpp"

bool argsAreCorrect(int ac, char **av){
    if (ac != 3) {
        return false;
    }
    std::string port(av[2]);
    for (char const &c : port) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

int main(int ac, char **av)
{
    if (!argsAreCorrect(ac, av)) {
        std::cout << "Usage: ./r-type_client <IP_ADRESS> <PORT>" << std::endl;
        return EXIT_FAILURE;
    }

    rtype::Game game;

    return game.run(av[1], std::stoi(av[2])) ? EXIT_SUCCESS : EXIT_FAILURE;
}