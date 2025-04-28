#pragma once

#include <string>
#include <vector>
#include <map>
#include <poll.h>
#include "Config.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class CommandHandler;

class Server {
public:
    Server(const Config& cfg);
    ~Server();
    bool initialize();
    void run();

private:
    int m_serverSocket;
    Config config;
    std::map<int, Client> m_clients;
    std::vector<Channel> channels;
    CommandHandler* cmdHandler;

    static bool shouldStop;
    static void signalHandler(int sig);

    bool setupSocket();
    void handleNewConnection(std::vector<pollfd>& fds);
    void handleClientData(int clientSocket, std::vector<pollfd>& fds);
    void removeClientFromChannels(int clientSocket);
    void removeClient(int clientSocket, std::vector<pollfd>& fds);
    void shutdown();

    friend class CommandHandler;
};

