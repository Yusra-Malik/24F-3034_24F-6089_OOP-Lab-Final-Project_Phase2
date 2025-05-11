#include "Stronghold.h"
#include <iostream>
using namespace std;
Economy::Economy() 
{
    taxRate = 0.1;
    inflationRate = 0.05;
    publicMoney = 10000;
}
void Economy::collectTax(int people[])
{
    int total = 0;
    for (int i = 0; i < totalClasses; i++)
    {
        total = total + people[i];
    }
    int taxAmount = total * 10 * taxRate;
    publicMoney = publicMoney + taxAmount;
    cout << "Tax collected: " << taxAmount << endl;
}
void Economy::increasePrices()
{
    inflationRate = inflationRate + 0.01;
    cout << "Inflation increased to " << inflationRate * 100 << " percent" << endl;
}
void Economy::spendMoney() 
{
    int spend = 500 + (rand() % 1000);
    if (publicMoney >= spend)
    {
        publicMoney = publicMoney - spend;
        cout << "Spent " << spend << " on public services" << endl;
    }
    else 
    {
        cout << "Not enough money to spend" << endl;
    }
}
void Economy::effectOfWar() 
{
    int loss = 1000 + (rand() % 2000);
    if (publicMoney >= loss) 
    {
        publicMoney = publicMoney - loss;
    }
    else 
    {
        publicMoney = 0;
    }
    inflationRate = inflationRate + 0.02;
    cout << "War caused a loss of " << loss << " coins" << endl;
}
void Economy::showEconomy() 
{
    cout << "\n--- Economy Status ---" << endl;
    cout << "Money: " << publicMoney << " coins" << endl;
    cout << "Tax rate: " << taxRate * 100 << " percent" << endl;
    cout << "Inflation rate: " << inflationRate * 100 << " percent" << endl;
}
