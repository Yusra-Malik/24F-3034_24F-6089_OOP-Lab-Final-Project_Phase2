#include "AllianceSystem.h"
#include <iostream>
#include <fstream>
using namespace std;

AllianceSystem::AllianceSystem() 
{
    player1Allies = new string[10];  
    player2Allies = new string[10];
    currentAllianceCount = 0;
    maxAlliances = 10; 
    allianceLogFile = "alliances_log.txt";
}

AllianceSystem::~AllianceSystem()
{
    delete[] player1Allies;
    delete[] player2Allies;
}

void AllianceSystem::formAlliance(const string& player1, const string& player2)
{
    if (currentAllianceCount == maxAlliances) 
{
        
        maxAlliances *= 2; 
        string* tempPlayer1 = new string[maxAlliances];
        string* tempPlayer2 = new string[maxAlliances];

        for (int i = 0; i < currentAllianceCount; ++i) 
        {
            tempPlayer1[i] = player1Allies[i];
            tempPlayer2[i] = player2Allies[i];
        }

      
        delete[] player1Allies;
        delete[] player2Allies;

        // Point to new arrays
        player1Allies = tempPlayer1;
        player2Allies = tempPlayer2;
    }

    // Add new alliance
    player1Allies[currentAllianceCount] = player1;
    player2Allies[currentAllianceCount] = player2;
    currentAllianceCount++;

    ofstream outFile(allianceLogFile.c_str(), ios::app);
    if (outFile.is_open()) {
        outFile << "Alliance formed between " << player1 << " and " << player2 << "\n";
        outFile.close();
        cout << "Alliance formed successfully.\n";
    }
    else {
        cout << "Error: Unable to open alliance log.\n";
    }
}

void AllianceSystem::breakAlliance(const string& player1, const string& player2) {
    for (int i = 0; i < currentAllianceCount; ++i) {
        if ((player1Allies[i] == player1 && player2Allies[i] == player2) ||
            (player1Allies[i] == player2 && player2Allies[i] == player1)) {
            // Break the alliance
            for (int j = i; j < currentAllianceCount - 1; ++j) {
                player1Allies[j] = player1Allies[j + 1];
                player2Allies[j] = player2Allies[j + 1];
            }
            currentAllianceCount--;

            ofstream outFile(allianceLogFile.c_str(), ios::app);
            if (outFile.is_open()) {
                outFile << "Alliance broken between " << player1 << " and " << player2 << "\n";
                outFile << "Consequence: Trust lost, potential conflict triggered.\n";
                outFile.close();
                cout << "Alliance broken.\n";
            }
            else {
                cout << "Error: Unable to open alliance log.\n";
            }
            return;
        }
    }
    cout << "No alliance exists between " << player1 << " and " << player2 << "\n";
}

void AllianceSystem::viewCurrentAlliances() const {
    cout << "--- Current Alliances ---\n";
    for (int i = 0; i < currentAllianceCount; ++i) {
        cout << player1Allies[i] << " <--> " << player2Allies[i] << "\n";
    }
}

void AllianceSystem::viewAllianceHistory() const {
    ifstream inFile(allianceLogFile.c_str());
    string line;
    if (inFile.is_open()) {
        cout << "--- Alliance History ---\n";
        while (getline(inFile, line)) {
            cout << line << "\n";
        }
        inFile.close();
    }
    else {
        cout << "Error: Unable to open alliance log.\n";
    }
}

bool AllianceSystem::isAllied(const string& player1, const string& player2) const {
    for (int i = 0; i < currentAllianceCount; ++i) {
        if ((player1Allies[i] == player1 && player2Allies[i] == player2) ||
            (player1Allies[i] == player2 && player2Allies[i] == player1)) {
            return true;
        }
    }
    return false;
}
