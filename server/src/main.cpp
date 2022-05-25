/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** main
*/

#include "RtypeServer.hpp"
#include "Protocol.hpp"
#include "RoomsManager.hpp"


bool argsAreCorrect(int ac, char **av){
    if (ac != 2) {
        return false;
    }
    for (char const &c : std::string(av[1])) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

int main(int ac, char **av)
{
    if (!argsAreCorrect(ac, av)) {
        std::cout << "Usage: ./r-type_server <PORT>" << std::endl;
        return EXIT_FAILURE;
    }
    rtype::Server server(std::atoi(av[1]), 49488);

    try {
        server.run();
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
    }
    return EXIT_SUCCESS;
}