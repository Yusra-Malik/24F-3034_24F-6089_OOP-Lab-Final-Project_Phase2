#ifndef KINGDOM_H
#define KINGDOM_H
#include <string>
using namespace std;
class Kingdom 
{
private:
    string name;
    int armyStrength;
    int resources;
    bool inWar;
public:
    Kingdom(string n, int army, int res);
    string getName();
    int getArmyStrength();
    int getResources();
    void gainResources(int r);
    void loseResources(int r);
    void setWarStatus(bool status);
    bool isInWar();
};
#endif

