#include "Stronghold.h"
#include <iostream>
using namespace std;


Military::Military()
{
    unitName = "";
    soldiers = 0;
    trainingLevel = 0;
    morale = 50;
    corruption = 0;
}

Military::Military(string name, int soldiers)
{
    unitName = name;
    this->soldiers = soldiers;
    trainingLevel = 0;
    morale = 50;
    corruption = 0;
}

void Military::recruit(int newSoldiers)
{
    soldiers += newSoldiers;
}
void Military::train(int trainingResources) 
{
    trainingLevel += trainingResources / 10; 
}
void Military::supply(int foodUnits, int weaponUnits) 
{
    morale += (foodUnits + weaponUnits) / 10; 
}
void Military::pay(int goldAmount) { 
    morale += goldAmount / 20;
}
void Military::simulateBattle(bool victory)
{
    morale += (victory ? 10 : -15); 
}
void Military::updateCorruption() 
{
    corruption += 5; 
}
void Military::displayStatus()
{
    cout << "Unit: " << unitName << ", Soldiers: " << soldiers << ", Morale: " << morale << ", Corruption: " << corruption << endl;
}

void Military::saveToFile(ofstream& outFile)
{
    outFile << unitName << " " << soldiers << " " << trainingLevel << " " << morale << " " << corruption << endl;
}

void Military::loadFromFile(ifstream& inFile)
{
    inFile >> unitName >> soldiers >> trainingLevel >> morale >> corruption;
}

string Military::getUnitName() 
{
    return unitName;
}
int Military::getSoldiers()
{
    return soldiers;
}
int Military::getTrainingLevel() 
{
    return trainingLevel; 
}
int Military::getMorale() 
{
    return morale; 
}
int Military::getCorruption()
{
    return corruption;
}

Military::~Military() {}

MilitaryManager::MilitaryManager()
{
    units = nullptr;
    numUnits = 0;
    capacity = 0;
}

MilitaryManager::MilitaryManager(int initialCapacity)
{
    capacity = initialCapacity;
    units = new Military * [capacity];
    numUnits = 0;
}

MilitaryManager::MilitaryManager(const MilitaryManager& other)
{
    capacity = other.capacity;
    numUnits = other.numUnits;
    units = new Military * [capacity];
    for (int i = 0; i < numUnits; i++)
    {
        units[i] = new Military(*other.units[i]);
    }
}

void MilitaryManager::addUnit(Military* newUnit)
{
    if (numUnits < capacity)
    {
        units[numUnits++] = newUnit;
    }
}

void MilitaryManager::simulateTrainingPhase(int trainingResources)
{
    for (int i = 0; i < numUnits; i++)
        units[i]->train(trainingResources);
}

void MilitaryManager::supplyAllUnits(int foodSupply, int weaponSupply)
{
    for (int i = 0; i < numUnits; i++)
        units[i]->supply(foodSupply, weaponSupply);
}

void MilitaryManager::payAllUnits(int totalGold)
{
    for (int i = 0; i < numUnits; i++)
        units[i]->pay(totalGold / numUnits);
}

void MilitaryManager::simulateBattles(bool* battleResults, int numBattles)
{
    for (int i = 0; i < numBattles && i < numUnits; i++)
    {
        units[i]->simulateBattle(battleResults[i]);
    }
}

void MilitaryManager::handleCorruption()
{
    for (int i = 0; i < numUnits; i++)
        units[i]->updateCorruption();
}

void MilitaryManager::displayAllUnits()
{
    for (int i = 0; i < numUnits; i++)
        units[i]->displayStatus();
}

void MilitaryManager::saveMilitary(const string& filename)
{
    ofstream outFile(filename);
    outFile << numUnits << endl;
    for (int i = 0; i < numUnits; i++)
    {
        units[i]->saveToFile(outFile);
    }
    outFile.close();
}

void MilitaryManager::loadMilitary(const string& filename)
{
    ifstream inFile(filename);
    inFile >> numUnits;
    units = new Military * [numUnits];
    for (int i = 0; i < numUnits; i++)
    {
        units[i] = new Military();
        units[i]->loadFromFile(inFile);
    }
    inFile.close();
}

MilitaryManager::~MilitaryManager()
{
    for (int i = 0; i < numUnits; i++)
        delete units[i];
    delete[] units;
}
