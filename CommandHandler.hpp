#pragma once

#include <string>
#include <vector>
#include <poll.h>
#include "Client.hpp"

class Server;
class Channel;

class CommandHandler {
public:
    CommandHandler(Server& s);
    void processCommand(int clientSocket, const std::string& input, std::vector<pollfd>& fds, size_t i);
    void broadcastMessage(int senderSocket, const std::string& message, std::vector<pollfd>& fds);

private:
    Server& server;

    bool checkClient(int clientSocket, std::vector<pollfd>& fds, Client*& client);
    void handlePassword(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleQuit(int clientSocket, Client& client, std::vector<pollfd>& fds);
    void handleNick(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleUser(const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i); // убрал clientSocket
    void handleJoin(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handlePrivmsg(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleWhois(const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleMode(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handlePing(const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleKick(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleInvite(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleTopic(int clientSocket, const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
    void handleUnknownCommand(const std::string& input, Client& client, std::vector<pollfd>& fds, size_t i);
};
