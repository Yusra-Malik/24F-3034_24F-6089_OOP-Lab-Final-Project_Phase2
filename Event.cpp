#include "Stronghold.h"
#include <iostream>
using namespace std;
Event::Event() {}
void Event::randomEvent(int people[], int& soldiers, Resource& res, Economy& eco)
{
    int event = rand() % 5;
    switch (event)
    {
    case 0:
        famine(people, res);
        break;
    case 1:
        war(soldiers, eco);
        break;
    case 2:
        disease(people);
        break;
    case 3:
        weatherDisaster(res);
        break;
    case 4:
        betrayal(eco);
        break;
    default:
        break;
    }
}
void Event::famine(int people[], Resource& res)
{
    int famineLoss = rand() % 50;
    people[0] = people[0] - famineLoss;
    res.useResource();
    cout << "Famine! Lost " << famineLoss << " people." << endl;
}
void Event::war(int& soldiers, Economy& eco)
{
    cout << "War breaks out!" << endl;
    soldiers = soldiers - 50;
    eco.effectOfWar();
}
void Event::disease(int people[])
{
    int diseaseLoss = rand() % 30;
    people[1] = people[1] - diseaseLoss;
    cout << "Disease strikes! Lost " << diseaseLoss << " people." << endl;
}
void Event::weatherDisaster(Resource& res)
{
    int loss = rand() % 100;
    res.useResource();
    cout << "Weather disaster! Lost " << loss << " units of resources." << endl;
}
void Event::betrayal(Economy& eco)
{
    int loss = rand() % 1000;
    eco.effectOfWar();
    cout << "Betrayal! Lost " << loss << " coins." << endl;
}
