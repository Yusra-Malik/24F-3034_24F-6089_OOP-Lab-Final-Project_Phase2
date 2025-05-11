
#include "TradeSystem.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

TradeSystem::TradeSystem()
{
    maxTrades = 10;
    tradeCount = 0;
    traders = new string[maxTrades];
    resourcesOffered = new string[maxTrades];
    goodsRequested = new string[maxTrades];
    tradeType = new string[maxTrades];
    tradeLogFile = "tradeLog.txt";
    srand(time(0));
}

TradeSystem::~TradeSystem()
{
    delete[] traders;
    delete[] resourcesOffered;
    delete[] goodsRequested;
    delete[] tradeType;
}

void TradeSystem::resizeIfNeeded()
{
    if (tradeCount == maxTrades) {
        maxTrades *= 2;
        string* newTraders = new string[maxTrades];
        string* newResources = new string[maxTrades];
        string* newGoods = new string[maxTrades];
        string* newTypes = new string[maxTrades];

        for (int i = 0; i < tradeCount; ++i) {
            newTraders[i] = traders[i];
            newResources[i] = resourcesOffered[i];
            newGoods[i] = goodsRequested[i];
            newTypes[i] = tradeType[i];
        }

        delete[] traders;
        delete[] resourcesOffered;
        delete[] goodsRequested;
        delete[] tradeType;

        traders = newTraders;
        resourcesOffered = newResources;
        goodsRequested = newGoods;
        tradeType = newTypes;
    }
}

void TradeSystem::offerTrade(const string& trader, const string& resource, const string& requestedGood) {
    resizeIfNeeded();

    traders[tradeCount] = trader;
    resourcesOffered[tradeCount] = resource;
    goodsRequested[tradeCount] = requestedGood;
    tradeType[tradeCount] = "Trade";
    tradeCount++;

    ofstream file(tradeLogFile.c_str(), ios::app);
    if (file.is_open()) {
        file << "TRADE: " << trader << " offered " << resource << " in exchange for " << requestedGood << "\n";
        file.close();
    }

    cout << "[Trade] Offer successfully logged.\n";
}

void TradeSystem::attemptSmuggle(const string& smuggler, const string& contraband, const string& destination) {
    resizeIfNeeded();
    bool caught = (rand() % 100) < 30;

    traders[tradeCount] = smuggler;
    resourcesOffered[tradeCount] = contraband;
    goodsRequested[tradeCount] = destination;
    tradeType[tradeCount] = "Smuggle";
    tradeCount++;

    ofstream file(tradeLogFile.c_str(), ios::app);
    if (file.is_open()) {
        if (caught) {
            file << "SMUGGLING FAILED: " << smuggler << " was caught trying to move " << contraband
                << " to " << destination << "\n";
            cout << "[Smuggling] Failed! " << smuggler << " was caught.\n";
        }
        else {
            file << "SMUGGLING SUCCESS: " << smuggler << " successfully moved " << contraband
                << " to " << destination << "\n";
            cout << "[Smuggling] Success! " << contraband << " delivered to " << destination << "\n";
        }
        file.close();
    }
}

void TradeSystem::imposeEmbargo(const string& traderName) {
    ofstream file(tradeLogFile.c_str(), ios::app);
    if (file.is_open()) {
        file << "EMBARGO: All trades and smuggling with " << traderName << " are blocked.\n";
        file.close();
    }
    cout << "[Embargo] Trade restrictions imposed on " << traderName << ".\n";
}

void TradeSystem::viewTradeHistory() const {
    ifstream file(tradeLogFile.c_str());
    string line;
    if (file.is_open()) {
        cout << "--- Trade and Smuggling History ---\n";
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }
    else {
        cout << "Unable to open trade log.\n";
    }
}
