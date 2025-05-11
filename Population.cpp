#include "Stronghold.h"
#include <iostream>
#include <fstream>
using namespace std;

Population::Population()
{
    name = "";
    size = 0;
    happiness = 50;
    health = 100;
}

Population::Population(string n, int s)
{
    name = n;
    size = s;
    happiness = 50;
    health = 100;
}

void Population::Grow(int shelter, int food, int employment)
{
    size += (shelter + food + employment) / 3;
}

void Population::Shrink(int disease, int warThreat)
{
    size -= (disease + warThreat) / 2;
    if (size < 0) size = 0;
}

bool Population::checkForRevolt()
{
    return (happiness < 30 || health < 30);
}

void Population::displayStatus()
{
    cout << "Population Group: " << name << endl;
    cout << "Size: " << size << ", Happiness: " << happiness << ", Health: " << health << endl;
}

string Population::getName()
{
    return name;
}

int Population::getSize()
{
    return size;
}

void Population::setSize(int s)
{
    size = s;
}

int Population::getHealth()
{
    return health;
}

void Population::setHealth(int h)
{
    health = h;
}

int Population::getHappiness()
{
    return happiness;
}

void Population::setHappiness(int hap)
{
    happiness = hap;
}

void Population::saveFile(ofstream& outFile)
{
    outFile << name << " " << size << " " << happiness << " " << health << endl;
}

void Population::loadFile(ifstream& inFile)
{
    inFile >> name >> size >> happiness >> health;
}

Population::~Population() {}

PopulationManager::PopulationManager()
{
    groups = nullptr;
    numGroups = 0;
}

PopulationManager::PopulationManager(int initialGroups)
{
    numGroups = initialGroups;
    groups = new Population * [numGroups];
    for (int i = 0; i < numGroups; i++) groups[i] = nullptr;
}

PopulationManager::PopulationManager(const PopulationManager& other)
{
    numGroups = other.numGroups;
    groups = new Population * [numGroups];
    for (int i = 0; i < numGroups; i++)
    {
        if (other.groups[i])
            groups[i] = new Population(*other.groups[i]);  
        else
            groups[i] = nullptr;
    }
}

void PopulationManager::addGroup(Population* newGroup)
{
    Population** temp = new Population * [numGroups + 1];
    for (int i = 0; i < numGroups; i++)
    {
        temp[i] = groups[i];
    }
    temp[numGroups] = newGroup;
    delete[] groups;
    groups = temp;
    numGroups++;
}

void PopulationManager::simulateYear(int foodSupply, int shelter, int employment, int disease, int war)
{
    for (int i = 0; i < numGroups; i++)
    {
        if (groups[i])
        {
            groups[i]->Grow(shelter, foodSupply, employment);
            groups[i]->Shrink(disease, war);
        }
    }
}

void PopulationManager::checkRevolts()
{
    for (int i = 0; i < numGroups; i++)
    {
        if (groups[i] && groups[i]->checkForRevolt())
            cout << groups[i]->getName() << " is revolting!" << endl;
    }
}

void PopulationManager::displayAll()
{
    for (int i = 0; i < numGroups; i++)
    {
        if (groups[i])
            groups[i]->displayStatus();
    }
}

void PopulationManager::saveGame(const string& filename)
{
    ofstream outFile(filename);
    outFile << numGroups << endl;
    for (int i = 0; i < numGroups; i++)
    {
        if (groups[i])
            groups[i]->saveFile(outFile);
    }
    outFile.close();
}

void PopulationManager::loadGame(const string& filename)
{
    ifstream inFile(filename);
    inFile >> numGroups;
    groups = new Population * [numGroups];
    for (int i = 0; i < numGroups; i++)
    {
        groups[i] = new Population();
        groups[i]->loadFile(inFile);
    }
    inFile.close();
}

void PopulationManager::logScoreAndResources(const string& logFilename, int resourcesUsed, int totalScore)
{
    ofstream logFile(logFilename, ios::app);
    logFile << "Resources Used: " << resourcesUsed << ", Total Score: " << totalScore << endl;
    logFile.close();
}

void PopulationManager::cleanUp()
{
    for (int i = 0; i < numGroups; i++)
    {
        if (groups[i])
        {
            delete groups[i];
            groups[i] = nullptr;
        }
    }
    delete[] groups;
    groups = nullptr;
}

PopulationManager::~PopulationManager()
{
    cleanUp();
}

