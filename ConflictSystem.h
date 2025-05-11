#ifndef CONFLICTSYSTEM_H
#define CONFLICTSYSTEM_H
#include "Kingdom.h"
using namespace std;
class ConflictSystem 
{
public:
    void declareWar(Kingdom* k1, Kingdom* k2);
    void resolveBattle(Kingdom* k1, Kingdom* k2);
    void betrayAlly(Kingdom* betrayer, Kingdom* ally);
};
#endif
