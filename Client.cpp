#include "Client.hpp"

Client::Client(int s)
    : socket(s), passwordEntered(false), passwordAttempts(3), nickname(""), username(""), realname(""), inputBuffer(""), outputBuffer("") {}

Client::Client()
    : socket(-1), passwordEntered(false), passwordAttempts(3), nickname(""), username(""), realname(""), inputBuffer(""), outputBuffer("") {}

int Client::getSocket() const { return socket; }
bool Client::isPasswordEntered() const { return passwordEntered; }
void Client::setPasswordEntered(bool value) { passwordEntered = value; }
int Client::getPasswordAttempts() const { return passwordAttempts; }
void Client::setPasswordAttempts(int attempts) { passwordAttempts = attempts; }
std::string Client::getNickname() const { return nickname; }
void Client::setNickname(const std::string& nick) { nickname = nick; }
std::string Client::getUsername() const { return username; }
void Client::setUsername(const std::string& user) { username = user; }
std::string Client::getRealname() const { return realname; }
void Client::setRealname(const std::string& name) { realname = name; }
std::string Client::getInputBuffer() const { return inputBuffer; }
void Client::appendInputBuffer(const std::string& data) { inputBuffer += data; }
void Client::clearInputBuffer() { inputBuffer = ""; }
std::string Client::getOutputBuffer() const { return outputBuffer; }
void Client::appendOutputBuffer(const std::string& data) { outputBuffer += data; }
void Client::eraseOutputBuffer(size_t bytes) { outputBuffer.erase(0, bytes); }