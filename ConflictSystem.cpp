#include "ConflictSystem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
void ConflictSystem::declareWar(Kingdom* k1, Kingdom* k2)
{
    cout << k1->getName() << " declared war on " << k2->getName() << endl;
    k1->setWarStatus(true);
    k2->setWarStatus(true);
    resolveBattle(k1, k2);
}
void ConflictSystem::resolveBattle(Kingdom* k1, Kingdom* k2) 
{
    srand(time(0));
    int power1 = k1->getArmyStrength() + rand() % 50;
    int power2 = k2->getArmyStrength() + rand() % 50;
    cout << "Battle between " << k1->getName() << " and " << k2->getName() << endl;
    cout << k1->getName() << " Power: " << power1 << endl;
    cout << k2->getName() << " Power: " << power2 << endl;
    if (power1 > power2)
    {
        cout << k1->getName() << " wins the battle!" << endl;
        k1->gainResources(30);
        k2->loseResources(30);
    }
    else
    {
        cout << k2->getName() << " defends successfully!" << endl;
        k2->gainResources(30);
        k1->loseResources(30);
    }
}
void ConflictSystem::betrayAlly(Kingdom* betrayer, Kingdom* ally) 
{
    cout << betrayer->getName() << " betrayed " << ally->getName() << endl;
    declareWar(betrayer, ally);
}
