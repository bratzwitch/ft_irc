#pragma once

#include <string>
#include <map>
#include <vector>

class Channel {
public:
    Channel(const std::string& n);
    void join(int clientSocket);
    void removeMember(int clientSocket);
    std::string getName() const;
    std::map<int, bool> getMembers() const;
    bool isOperator(int clientSocket) const;
    std::string getTopic() const;
    void setTopic(const std::string& t);
    bool isInviteOnly() const;
    void setInviteOnly(bool value);
    bool isTopicRestricted() const;
    void setTopicRestricted(bool value);
    std::string getKey() const;
    void setKey(const std::string& k);
    void setOperator(int clientSocket, bool value);
    int getUserLimit() const;
    void setUserLimit(int limit);
    void invite(int clientSocket);
    bool isInvited(int clientSocket) const;

private:
    std::string name;
    std::map<int, bool> members; // socket -> isOperator
    std::string topic;
    bool inviteOnly;
    bool topicRestricted;
    std::string key;
    int userLimit;
    std::vector<int> invited;
};

