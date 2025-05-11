#ifndef ALLIANCESYSTEM_H
#define ALLIANCESYSTEM_H

#include <string>
using namespace std;

class AllianceSystem 
{
private:
    string* player1Allies;  
    string* player2Allies;  
    int currentAllianceCount;  
    int maxAlliances;  
    string allianceLogFile;

public:
    AllianceSystem();  
    
    void formAlliance(const string& player1, const string& player2);
    void breakAlliance(const string& player1, const string& player2);
    void viewCurrentAlliances() const;
    void viewAllianceHistory() const;
    bool isAllied(const string& player1, const string& player2) const;

    ~AllianceSystem();
};

#endif
