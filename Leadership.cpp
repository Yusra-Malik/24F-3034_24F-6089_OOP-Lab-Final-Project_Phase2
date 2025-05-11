#include "Stronghold.h"
#include <iostream>
using namespace std;

Leader::Leader()
{
    name = "";
    leadershipStyle = "";
    militarySupport = 50;
    economyFocus = 50;
    freedomFocus = 50;
    popularity = 50;
}

Leader::Leader(string n, string style)
{
    name = n;
    leadershipStyle = style;
    militarySupport = 50;
    economyFocus = 50;
    freedomFocus = 50;
    popularity = 50;
}

void Leader::displayInfo()
{
    cout << "Leader: " << name << " (" << leadershipStyle << ")" << endl;
}

void Leader::improvePopularity(int amount) 
{
    popularity += amount;
}
void Leader::losePopularity(int amount)
{
    popularity -= amount; 
}
void Leader::strengthenMilitarySupport(int amount)
{
    militarySupport += amount;
}
void Leader::weakenMilitarySupport(int amount) 
{
    militarySupport -= amount; 
}

string Leader::getName() 
{
    return name;
}
string Leader::getLeadershipStyle() 
{
    return leadershipStyle; 
}
int Leader::getMilitarySupport()
{
    return militarySupport; 
}
int Leader::getEconomyFocus()
{
    return economyFocus; 
}
int Leader::getFreedomFocus() 
{
    return freedomFocus; 
}
int Leader::getPopularity() 
{
    return popularity;
}

void Leader::saveToFile(ofstream& outFile)
{
    outFile << name << " " << leadershipStyle << " " << militarySupport << " " << economyFocus << " " << freedomFocus << " " << popularity << endl;
}

void Leader::loadFromFile(ifstream& inFile)
{
    inFile >> name >> leadershipStyle >> militarySupport >> economyFocus >> freedomFocus >> popularity;
}

Leader::~Leader() {}


LeadershipSystem::LeadershipSystem()
{
    currentLeader = nullptr;
    yearCount = 0;
}

LeadershipSystem::LeadershipSystem(Leader* initialLeader)
{
    currentLeader = initialLeader;
    yearCount = 0;
}

LeadershipSystem::LeadershipSystem(const LeadershipSystem& other)
{
    if (other.currentLeader)
        currentLeader = new Leader(*other.currentLeader);
    else
        currentLeader = nullptr;
    yearCount = other.yearCount;
}

void LeadershipSystem::conductElection(string newLeaderName, string newStyle)
{
    delete currentLeader;
    currentLeader = new Leader(newLeaderName, newStyle);
}

void LeadershipSystem::attemptCoup()
{
    if (currentLeader)
        currentLeader->losePopularity(30);
}

void LeadershipSystem::naturalSuccession(string heirName, string style)
{
    delete currentLeader;
    currentLeader = new Leader(heirName, style);
}

void LeadershipSystem::simulateYear()
{
    yearCount++;
    if (currentLeader)
        currentLeader->improvePopularity(5);
}

void LeadershipSystem::displayCurrentLeader()
{
    if (currentLeader)
        currentLeader->displayInfo();
}

void LeadershipSystem::saveLeadership(const string& filename)
{
    ofstream outFile(filename);
    if (currentLeader)
        currentLeader->saveToFile(outFile);
    outFile.close();
}

void LeadershipSystem::loadLeadership(const string& filename)
{
    ifstream inFile(filename);
    if (!currentLeader)
        currentLeader = new Leader();
    currentLeader->loadFromFile(inFile);
    inFile.close();
}

LeadershipSystem::~LeadershipSystem()
{
    delete currentLeader;
}
