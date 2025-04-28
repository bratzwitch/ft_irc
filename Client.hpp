#pragma once

#include <string>

class Client {
public:
    Client(int s);
    Client();
    int getSocket() const;
    bool isPasswordEntered() const;
    void setPasswordEntered(bool value);
    int getPasswordAttempts() const;
    void setPasswordAttempts(int attempts);
    std::string getNickname() const;
    void setNickname(const std::string& nick);
    std::string getUsername() const;
    void setUsername(const std::string& user);
    std::string getRealname() const;
    void setRealname(const std::string& name);
    std::string getInputBuffer() const;
    void appendInputBuffer(const std::string& data);
    void clearInputBuffer();
    std::string getOutputBuffer() const;
    void appendOutputBuffer(const std::string& data);
    void eraseOutputBuffer(size_t bytes);

private:
    int socket;
    bool passwordEntered;
    int passwordAttempts;
    std::string nickname;
    std::string username;
    std::string realname;
    std::string inputBuffer;
    std::string outputBuffer;
};