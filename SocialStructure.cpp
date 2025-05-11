#include "Stronghold.h"
#include <iostream>
using namespace std;


SocialStructure::SocialStructure()
{
    name = "";
    population = 0;
    wealth = 0;
    power = 0;
}

SocialStructure::SocialStructure(string n, int p, int w, int po)
{
    name = n;
    population = p;
    wealth = w;
    power = po;
}

string SocialStructure::getName()
{
    return name; 
}
void SocialStructure::setName(string n) 
{
    name = n;
}
int SocialStructure::getPopulation() 
{
    return population;
}
void SocialStructure::setPopulation(int p) 
{
    population = p;
}
int SocialStructure::getWealth() 
{
    return wealth; 
}
void SocialStructure::setWealth(int w) 
{
    wealth = w;
}
int SocialStructure::getPower() 
{
    return power; 
}
void SocialStructure::setPower(int po) 
{
    power = po;
}

SocialStructure::~SocialStructure() 
{}

Merchants::Merchants() : SocialStructure("Merchants", 100, 200, 50) {}
Merchants::Merchants(int p) : SocialStructure("Merchants", p, 200, 50) {}

void Merchants::classInteraction(SocialStructure* other)
{
    wealth += 10;
    power += 5;
}


Peasants::Peasants() : SocialStructure("Peasants", 300, 50, 20) {}
Peasants::Peasants(int p) : SocialStructure("Peasants", p, 50, 20) {}

void Peasants::classInteraction(SocialStructure* other)
{
    wealth += 5;
    
}


Nobles::Nobles() : SocialStructure("Nobles", 50, 500, 200) {}
Nobles::Nobles(int p) : SocialStructure("Nobles", p, 500, 200) {}

void Nobles::classInteraction(SocialStructure* other)
{
    power += 15;
}


Migrants::Migrants() : SocialStructure("Migrants", 50, 20, 5) {}
Migrants::Migrants(int p) : SocialStructure("Migrants", p, 20, 5) {}

void Migrants::classInteraction(SocialStructure* other)
{
    population += 5;
}


Scholars::Scholars() : SocialStructure("Scholars", 30, 100, 30) {}
Scholars::Scholars(int p) : SocialStructure("Scholars", p, 100, 30) {}

void Scholars::classInteraction(SocialStructure* other)
{
    wealth += 10;
}


Soldiers::Soldiers() : SocialStructure("Soldiers", 100, 100, 150) {}
Soldiers::Soldiers(int p) : SocialStructure("Soldiers", p, 100, 150) {}

void Soldiers::classInteraction(SocialStructure* other)
{
    power += 20;
}
