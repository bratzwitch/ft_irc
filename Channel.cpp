#include "Channel.hpp"
#include <iostream>

Channel::Channel(const std::string& n)
    : name(n), topic(""), inviteOnly(false), topicRestricted(false), key(""), userLimit(0) {}

void Channel::join(int clientSocket) {
    if (members.empty()) {
        members[clientSocket] = true;
    } else {
        members[clientSocket] = false;
    }

    for (std::vector<int>::iterator it = invited.begin(); it != invited.end(); ++it) {
        if (*it == clientSocket) {
            invited.erase(it);
            break;
        }
    }
}

void Channel::removeMember(int clientSocket) {
    std::cout << "Removing socket " << clientSocket << " from channel " << name << ", members before: " << members.size() << std::endl;
    members.erase(clientSocket);
    std::cout << "After removing socket " << clientSocket << ", members left: " << members.size() << std::endl;
    for (std::vector<int>::iterator it = invited.begin(); it != invited.end(); ++it) {
        if (*it == clientSocket) {
            invited.erase(it);
            break;
        }
    }
    bool hasOperator = false;
    for (std::map<int, bool>::iterator it = members.begin(); it != members.end(); ++it) {
        if (it->second == true) {
            hasOperator = true;
            break;
        }
    }
    if (!hasOperator && !members.empty()) {
        std::map<int, bool>::iterator firstMember = members.begin();
        setOperator(firstMember->first, true);
        std::cout << "Promoted client " << firstMember->first << " to operator in channel " << name << std::endl;
    }
}
std::string Channel::getName() const { return name; }

std::map<int, bool> Channel::getMembers() const { return members; }

bool Channel::isOperator(int clientSocket) const {
    std::map<int, bool>::const_iterator it = members.find(clientSocket);
    return (it != members.end() && it->second);
}

std::string Channel::getTopic() const { return topic; }

void Channel::setTopic(const std::string& t) { topic = t; }

bool Channel::isInviteOnly() const { return inviteOnly; }

void Channel::setInviteOnly(bool value) { inviteOnly = value; }

bool Channel::isTopicRestricted() const { return topicRestricted; }

void Channel::setTopicRestricted(bool value) { topicRestricted = value; }

std::string Channel::getKey() const { return key; }

void Channel::setKey(const std::string& k) { key = k; }

void Channel::setOperator(int clientSocket, bool value) {
    std::map<int, bool>::iterator it = members.find(clientSocket);
    if (it != members.end()) {
        it->second = value;
    }
}

int Channel::getUserLimit() const { return userLimit; }

void Channel::setUserLimit(int limit) { userLimit = limit; }

void Channel::invite(int clientSocket) {
    invited.push_back(clientSocket);
}

bool Channel::isInvited(int clientSocket) const {
    for (std::vector<int>::const_iterator it = invited.begin(); it != invited.end(); ++it) {
        if (*it == clientSocket) return true;
    }
    return false;
}