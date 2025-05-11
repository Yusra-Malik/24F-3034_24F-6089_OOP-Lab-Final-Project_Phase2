#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H

#include <string>
using namespace std;

class CommunicationSystem 
{
private:
    string chatLogFile;

public:
    CommunicationSystem(); 
    void sendMessage(const string& sender, const string& receiver, const string& message);
    void viewAllMessages() const;
    void viewMessagesFromSender(const string& sender) const;
};

#endif

