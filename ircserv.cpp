#include <cstdlib>
#include <iostream>
#include <string>
#include "Server.hpp"
#include "Config.hpp"

bool is_valid_number(const char* str) {
    if (!str || str[0] == '\0')
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }

    if (!is_valid_number(argv[1])) {
        std::cerr << "Error: Port must be a valid number" << std::endl;
        return 1;
    }
    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        std::cerr << "Error: Port must be between 1 and 65535" << std::endl;
        return 1;
    }

    std::string password = argv[2];
    if (password.empty()) {
        std::cerr << "Error: Password cannot be empty" << std::endl;
        return 1;
    }

    std::cout << "Starting IRC server on port " << port << " with password: " << password << std::endl;

    try {
        Config config(port, password);
        Server server(config);
        if (!server.initialize()) {
            return 1;
        }
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}