#include "Config.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <sstream> 

/* Definition of static constants */
const int Config::MIN_PORT = 1;
const int Config::MAX_PORT = 65535;
const size_t Config::MIN_PASSWORD_LENGTH = 4;

/* Constructor initializes Config object with a port number and password.
   Validates port and password before assignment. */
Config::Config(int p, const std::string& pw) {
    validatePort(p);
    validatePassword(pw);
    port = p;
    password = pw;
}

/* Returns the port number */
int Config::getPort() const {
    return port;
}

/* Returns the password */
std::string Config::getPassword() const {
    return password;
}

/* Validates the port number.
   Throws an exception if the port is not within the allowed range (1-65535). */
void Config::validatePort(int p) const {
    if (p < MIN_PORT || p > MAX_PORT) {
        std::ostringstream oss;
        oss << "Port must be between " << MIN_PORT << " and " << MAX_PORT;
        throw std::runtime_error(oss.str());
    }
}

/* Validates the password.
   Throws an exception if the password is empty, too short, or consists only of spaces. */
void Config::validatePassword(const std::string& pw) const {
    if (pw.empty()) {
        throw std::runtime_error("Password cannot be empty");
    }
    if (pw.length() < MIN_PASSWORD_LENGTH) {
        std::ostringstream oss;
        oss << "Password must be at least " << MIN_PASSWORD_LENGTH << " characters long";
        throw std::runtime_error(oss.str());
    }
    bool allSpaces = true;
    for (size_t i = 0; i < pw.length(); ++i) {
        if (pw[i] != ' ') {
            allSpaces = false;
            break;
        }
    }
    if (allSpaces) {
        throw std::runtime_error("Password cannot consist only of spaces");
    }
}

/* Loads configuration from a file (optional).
   Reads port and password from the specified file.
   Returns true on success, false on failure. */
bool Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open config file " << filename << std::endl;
        return false;
    }

    int newPort;
    std::string newPassword;
    if (!(file >> newPort >> newPassword)) {
        std::cerr << "Warning: Invalid config file format" << std::endl;
        file.close();
        return false;
    }

    try {
        validatePort(newPort);
        validatePassword(newPassword);
        port = newPort;
        password = newPassword;
    } catch (const std::runtime_error& e) {
        std::cerr << "Config file error: " << e.what() << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}
