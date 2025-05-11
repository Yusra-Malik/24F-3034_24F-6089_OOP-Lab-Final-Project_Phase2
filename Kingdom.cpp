#include "Kingdom.h"
Kingdom::Kingdom(string n, int army, int res) 
{
    name = n;
    armyStrength = army;
    resources = res;
    inWar = false;
}
string Kingdom::getName() 
{
    return name;
}
int Kingdom::getArmyStrength()
{
    return armyStrength;
}
int Kingdom::getResources() 
{
    return resources;
}
void Kingdom::gainResources(int r)
{
    resources += r;
}
void Kingdom::loseResources(int r)
{
    resources -= r;
    if (resources < 0) resources = 0;
}
void Kingdom::setWarStatus(bool status) 
{
    inWar = status;
}
bool Kingdom::isInWar()
{
    return inWar;
}
