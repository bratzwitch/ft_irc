#pragma once

#include <string>

class Config {
public:
    Config(int p, const std::string& pw);
    int getPort() const;
    std::string getPassword() const;
    bool loadFromFile(const std::string& filename); /* optional */

private:
    int port;
    std::string password;

    void validatePort(int p) const;
    void validatePassword(const std::string& pw) const;

    static const int MIN_PORT;
    static const int MAX_PORT;
    static const size_t MIN_PASSWORD_LENGTH;
};

