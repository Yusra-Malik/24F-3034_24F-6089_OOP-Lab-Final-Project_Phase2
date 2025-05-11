
#ifndef TRADESYSTEM_H
#define TRADESYSTEM_H

#include <string>
using namespace std;

class TradeSystem
{
private:
    string* traders;
    string* resourcesOffered;
    string* goodsRequested;
    string* tradeType;
    int tradeCount;
    int maxTrades;
    string tradeLogFile;

    void resizeIfNeeded(); 

public:
    TradeSystem();
    ~TradeSystem();

    void offerTrade(const string& trader, const string& resource, const string& requestedGood);
    void attemptSmuggle(const string& smuggler, const string& contraband, const string& destination);
    void imposeEmbargo(const string& traderName);
    void viewTradeHistory() const;
};

#endif
