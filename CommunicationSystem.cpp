#include "Stronghold.h"
#include <iostream>
#include <fstream>
using namespace std;

CommunicationSystem::CommunicationSystem() 
{
    chatLogFile = "chat_log.txt";
}

void CommunicationSystem::sendMessage(const string& sender, const string& receiver, const string& message)
{
    ofstream outFile(chatLogFile.c_str(), ios::app);
    if (outFile.is_open())
    {
        outFile << "From: " << sender << " To: " << receiver << " | " << message << "\n";
        outFile.close();
        cout << "Message sent.\n";
    }
    else 
    {
        cout << "Error: Unable to open chat log.\n";
    }
}

void CommunicationSystem::viewAllMessages() const
{
    ifstream inFile(chatLogFile.c_str());
    string line;
    if (inFile.is_open())
    {
        cout << "--- Chat History ---\n";
        while (getline(inFile, line)) {
            cout << line << "\n";
        }
        inFile.close();
    }
    else {
        cout << "Error: Unable to open chat log.\n";
    }
}

void CommunicationSystem::viewMessagesFromSender(const string& sender) const {
    ifstream inFile(chatLogFile.c_str());
    string line;
    if (inFile.is_open()) {
        cout << "--- Messages from " << sender << " ---\n";
        while (getline(inFile, line)) {
            if (line.find("From: " + sender + " ") != string::npos) {
                cout << line << "\n";
            }
        }
        inFile.close();
    }
    else {
        cout << "Error: Unable to open chat log.\n";
    }
}
