# ft_irc

An IRC (Internet Relay Chat) server implementation in C++ that supports multiple clients, channels, and standard IRC commands.

## Description

ft_irc is a project that involves creating an IRC server from scratch using C++. It teaches network programming, socket management, concurrent client handling, and the IRC protocol implementation. The server supports multiple clients, channels, user authentication, and standard IRC commands.

## Features

- **Multi-client Support**: Handle multiple simultaneous connections
- **Channel Management**: Create, join, and manage IRC channels
- **User Authentication**: Nickname and user registration
- **IRC Commands**: Standard IRC command set implementation
- **Operator Privileges**: Channel operators with special permissions
- **Message Broadcasting**: Send messages to channels and users
- **Non-blocking I/O**: Efficient socket management using select()
- **Protocol Compliance**: Follows RFC 1459 IRC protocol standards

## Supported IRC Commands

### Connection Commands
- `PASS`: Set connection password
- `NICK`: Set or change nickname
- `USER`: Specify user information
- `QUIT`: Disconnect from server

### Channel Commands
- `JOIN`: Join a channel
- `PART`: Leave a channel
- `TOPIC`: View or set channel topic
- `NAMES`: List users in channel
- `LIST`: List available channels
- `KICK`: Remove user from channel (operator)
- `INVITE`: Invite user to channel (operator)
- `MODE`: Change channel or user modes

### Communication Commands
- `PRIVMSG`: Send private message
- `NOTICE`: Send notice message
- `PING`: Server ping
- `PONG`: Ping response

### Operator Commands
- `OPER`: Gain operator privileges
- `KILL`: Disconnect user (operator)
- `WALLOPS`: Send message to all operators

## Compilation

```bash
make
```

## Usage

1. Clone the repository:
```bash
git clone https://github.com/bratzwitch/ft_irc.git
cd ft_irc
```

2. Compile the server:
```bash
make
```

3. Start the IRC server:
```bash
./ircserv <port> <password>
```

**Example:**
```bash
./ircserv 6667 mypassword
```

4. Connect with an IRC client:
```bash
# Using netcat
nc localhost 6667

# Using irssi
irssi -c localhost -p 6667

# Using HexChat, Weechat, or other IRC clients
```

## Connection Example

**Client connection sequence:**
```
Client: PASS mypassword
Client: NICK john_doe
Client: USER john 0 * :John Doe
Server: :server 001 john_doe :Welcome to the IRC server
Server: :server 002 john_doe :Your host is server
Server: :server 003 john_doe :This server was created...
Server: :server 004 john_doe server 1.0 io mnps
```

**Join channel and chat:**
```
Client: JOIN #general
Server: :john_doe JOIN #general
Server: :server 353 john_doe = #general :john_doe
Server: :server 366 john_doe #general :End of NAMES list

Client: PRIVMSG #general :Hello everyone!
Server: :john_doe PRIVMSG #general :Hello everyone!
```

## Implementation Details

### Server Architecture

```cpp
class IRCServer {
private:
    int                     serverSocket;
    int                     port;
    std::string            password;
    fd_set                 readFds;
    std::vector<Client*>   clients;
    std::vector<Channel*>  channels;
    
public:
    IRCServer(int port, const std::string& password);
    ~IRCServer();
    
    void    start();
    void    acceptNewClient();
    void    handleClientMessage(Client* client);
    void    removeClient(Client* client);
};
```

### Client Management

```cpp
class Client {
private:
    int         socket;
    std::string nickname;
    std::string username;
    std::string realname;
    std::string hostname;
    bool        authenticated;
    bool        registered;
    
public:
    Client(int socket);
    ~Client();
    
    void        sendMessage(const std::string& message);
    std::string receiveMessage();
    bool        isRegistered() const;
    void        setNickname(const std::string& nick);
};
```

### Channel Implementation

```cpp
class Channel {
private:
    std::string                 name;
    std::string                 topic;
    std::vector<Client*>        members;
    std::vector<Client*>        operators;
    std::map<char, bool>        modes;
    
public:
    Channel(const std::string& name);
    ~Channel();
    
    void    addMember(Client* client);
    void    removeMember(Client* client);
    void    broadcastMessage(const std::string& message, Client* sender = nullptr);
    bool    isOperator(Client* client) const;
    void    setTopic(const std::string& topic);
};
```

### Command Processing

```cpp
class CommandHandler {
private:
    IRCServer*  server;
    
    void    handlePass(Client* client, const std::vector<std::string>& params);
    void    handleNick(Client* client, const std::vector<std::string>& params);
    void    handleUser(Client* client, const std::vector<std::string>& params);
    void    handleJoin(Client* client, const std::vector<std::string>& params);
    void    handlePrivmsg(Client* client, const std::vector<std::string>& params);
    void    handleQuit(Client* client, const std::vector<std::string>& params);
    
public:
    CommandHandler(IRCServer* server);
    void    processCommand(Client* client, const std::string& message);
};
```

## File Structure

```
ft_irc/
├── src/
│   ├── main.cpp              # Program entry point
│   ├── IRCServer.cpp         # Main server class
│   ├── Client.cpp            # Client management
│   ├── Channel.cpp           # Channel management
│   ├── CommandHandler.cpp    # IRC command processing
│   └── utils.cpp             # Helper functions
├── include/
│   ├── IRCServer.hpp         # Server header
│   ├── Client.hpp            # Client header
│   ├── Channel.hpp           # Channel header
│   └── CommandHandler.hpp    # Command handler header
├── Makefile                  # Compilation rules
└── README.md                 # This file
```

## Network Programming Concepts

### Socket Programming

```cpp
void IRCServer::initializeSocket() {
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        throw std::runtime_error("Failed to create socket");
    
    // Set socket options
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Bind to address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
        throw std::runtime_error("Failed to bind socket");
    
    // Listen for connections
    if (listen(serverSocket, SOMAXCONN) == -1)
        throw std::runtime_error("Failed to listen on socket");
}
```

### Select() for I/O Multiplexing

```cpp
void IRCServer::handleConnections() {
    while (true) {
        FD_ZERO(&readFds);
        FD_SET(serverSocket, &readFds);
        int maxFd = serverSocket;
        
        // Add client sockets to set
        for (Client* client : clients) {
            FD_SET(client->getSocket(), &readFds);
            maxFd = std::max(maxFd, client->getSocket());
        }
        
        // Wait for activity
        int activity = select(maxFd + 1, &readFds, nullptr, nullptr, nullptr);
        if (activity < 0)
            throw std::runtime_error("Select error");
        
        // Check for new connections
        if (FD_ISSET(serverSocket, &readFds))
            acceptNewClient();
        
        // Check existing clients
        for (Client* client : clients) {
            if (FD_ISSET(client->getSocket(), &readFds))
                handleClientMessage(client);
        }
    }
}
```

## IRC Protocol Implementation

### Message Format
IRC messages follow this format:
```
[:prefix] <command> [parameters] [:trailing]
```

### Response Codes
```cpp
#define RPL_WELCOME          001
#define RPL_YOURHOST         002
#define RPL_CREATED          003
#define RPL_MYINFO           004
#define RPL_TOPIC            332
#define RPL_NAMREPLY         353
#define RPL_ENDOFNAMES       366

#define ERR_NOSUCHNICK       401
#define ERR_NOSUCHCHANNEL    403
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_NICKNAMEINUSE    433
#define ERR_NEEDMOREPARAMS   461
```

### Example Command Implementation

```cpp
void CommandHandler::handleJoin(Client* client, const std::vector<std::string>& params) {
    if (params.empty()) {
        client->sendMessage(":server 461 " + client->getNickname() + " JOIN :Not enough parameters");
        return;
    }
    
    std::string channelName = params[0];
    if (channelName[0] != '#') {
        client->sendMessage(":server 403 " + client->getNickname() + " " + channelName + " :No such channel");
        return;
    }
    
    Channel* channel = server->findOrCreateChannel(channelName);
    if (channel->isMember(client)) {
        return; // Already in channel
    }
    
    channel->addMember(client);
    
    // Send JOIN confirmation
    std::string joinMsg = ":" + client->getNickname() + " JOIN " + channelName;
    channel->broadcastMessage(joinMsg);
    
    // Send topic if exists
    if (!channel->getTopic().empty()) {
        client->sendMessage(":server 332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic());
    }
    
    // Send names list
    std::string namesList = channel->getNamesString();
    client->sendMessage(":server 353 " + client->getNickname() + " = " + channelName + " :" + namesList);
    client->sendMessage(":server 366 " + client->getNickname() + " " + channelName + " :End of NAMES list");
}
```

## Testing

### Manual Testing with netcat
```bash
# Terminal 1: Start server
./ircserv 6667 password123

# Terminal 2: Client 1
nc localhost 6667
PASS password123
NICK alice
USER alice 0 * :Alice Smith
JOIN #test
PRIVMSG #test :Hello from Alice!

# Terminal 3: Client 2
nc localhost 6667
PASS password123
NICK bob
USER bob 0 * :Bob Jones
JOIN #test
PRIVMSG #test :Hello from Bob!
```

### Testing with IRC Clients
```bash
# Test with irssi
irssi -c localhost -p 6667 -w password123

# Commands to test
/nick testuser
/join #general
/msg #general Hello everyone!
/part #general
/quit Goodbye!
```

## Error Handling

### Common Error Scenarios
- **Invalid password**: Reject connection
- **Nickname conflicts**: Send ERR_NICKNAMEINUSE
- **Missing parameters**: Send ERR_NEEDMOREPARAMS
- **Channel not found**: Send ERR_NOSUCHCHANNEL
- **Insufficient privileges**: Send ERR_CHANOPRIVSNEEDED

### Connection Handling
```cpp
void IRCServer::handleClientDisconnection(Client* client) {
    // Remove from all channels
    for (Channel* channel : channels) {
        if (channel->isMember(client)) {
            channel->removeMember(client);
            
            // Send PART message to channel
            std::string partMsg = ":" + client->getNickname() + " PART " + channel->getName() + " :Connection lost";
            channel->broadcastMessage(partMsg);
        }
    }
    
    // Close socket and remove client
    close(client->getSocket());
    removeClientFromList(client);
    delete client;
}
```

## Requirements

- **C++98**: Code must compile with C++98 standard
- **Unix Sockets**: Network programming with BSD sockets
- **Non-blocking I/O**: Must not block on any operation
- **RFC 1459**: Follow IRC protocol standards
- **Memory Management**: No memory leaks

## Compilation Flags

```bash
c++ -Wall -Wextra -Werror -std=c++98 -I./include src/*.cpp -o ircserv
```

## Resources

- **RFC 1459**: Internet Relay Chat Protocol
- **RFC 2812**: Internet Relay Chat: Client Protocol
- **Beej's Guide**: Network Programming tutorial
- **IRC Clients**: irssi, HexChat, Weechat for testing

## Author

Viacheslav Moroz - 42 Student
