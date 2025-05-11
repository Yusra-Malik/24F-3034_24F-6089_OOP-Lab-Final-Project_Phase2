#include "Stronghold.h"
#include <iostream>
using namespace std;
Resource::Resource()
{
    resourceName[0] = "Food";
    resourceName[1] = "Wood";
    resourceName[2] = "Stone";
    resourceName[3] = "Iron";
    resourceName[4] = "Gold";
    for (int i = 0; i < totalResources; i++)
    {
        resourceAmount[i] = 100; 
    }
}
void Resource::collectResource()
{
    int resourceType;
    int amount;
    cout << "Select resource to collect:\n";
    for (int i = 0; i < totalResources; i++)
    {
        cout << i + 1 << ". " << resourceName[i] << endl;
    }
    cout << "Enter the number of resource to collect: ";
    cin >> resourceType;
    if (resourceType < 1 || resourceType > totalResources)
    {
        cout << "Invalid resource type!" << endl;
        return;
    }
    cout << "How much " << resourceName[resourceType - 1] << " do you want to collect? ";
    cin >> amount;
    resourceAmount[resourceType - 1] += amount;
    cout << "Collected " << amount << " units of " << resourceName[resourceType - 1] << "." << endl;
}
void Resource::useResource()
{
    int resourceType;
    int amount;
    cout << "Select resource to use:\n";
    for (int i = 0; i < totalResources; i++) 
    {
        cout << i + 1 << ". " << resourceName[i] << " (Available: " << resourceAmount[i] << " units)" << endl;
    }
    cout << "Enter the number of resource to use: ";
    cin >> resourceType;
    if (resourceType < 1 || resourceType > totalResources) {
        cout << "Invalid resource type!" << endl;
        return;
    }
    cout << "How much " << resourceName[resourceType - 1] << " do you want to use? ";
    cin >> amount;
    if (amount > resourceAmount[resourceType - 1]) 
    {
        cout << "Not enough resources!" << endl;
        return;
    }
    resourceAmount[resourceType - 1] -= amount;
    cout << "Used " << amount << " units of " << resourceName[resourceType - 1] << "." << endl;
}
void Resource::tradeResource() 
{
    int resourceType;
    int amount;
    int tradeValue;
    cout << "Select resource to trade:\n";
    for (int i = 0; i < totalResources; i++)
    {
        cout << i + 1 << ". " << resourceName[i] << " (Available: " << resourceAmount[i] << " units)" << endl;
    }
    cout << "Enter the number of resource to trade: ";
    cin >> resourceType;
    if (resourceType < 1 || resourceType > totalResources) {
        cout << "Invalid resource type!" << endl;
        return;
    }
    cout << "How much " << resourceName[resourceType - 1] << " do you want to trade? ";
    cin >> amount;
    if (amount > resourceAmount[resourceType - 1]) 
    {
        cout << "Not enough resources!" << endl;
        return;
    }
    tradeValue = amount * 2;
    resourceAmount[resourceType - 1] -= amount;
    cout << "Traded " << amount << " units of " << resourceName[resourceType - 1] << " for " << tradeValue << " coins." << endl;
}
void Resource::showResources() 
{
    cout << "\n--- Resource Status ---" << endl;
    for (int i = 0; i < totalResources; i++) 
    {
        cout << resourceName[i] << ": " << resourceAmount[i] << " units" << endl;
    }
}
